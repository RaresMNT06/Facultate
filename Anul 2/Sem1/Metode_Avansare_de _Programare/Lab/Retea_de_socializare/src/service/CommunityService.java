package service;

import model.Friendship;
import model.Tuple;
import model.User;
import repository.Repository;

import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Operatii pe reteaua vazuta ca graf: utilizatorii sunt noduri, prieteniile sunt muchii.
 */
public class CommunityService {

    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;

    /**
     * @param userRepository       - repository-ul de utilizatori
     * @param friendshipRepository - repository-ul de prietenii
     */
    public CommunityService(Repository<Long, User> userRepository,
                            Repository<Tuple<Long, Long>, Friendship> friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    /**
     * @return numarul de comunitati (componente conexe)
     */
    public int countCommunities() {
        return getCommunities().size();
    }

    /**
     * comunitatea cea mai sociabila este cea care contine cel mai lung drum
     *
     * @return utilizatorii din comunitatea cea mai sociabila, sortati dupa nume si prenume
     * (lista goala daca nu exista utilizatori)
     */
    public List<User> getMostSociableCommunity() {
        Map<Long, List<Long>> graph = buildGraph();
        return getCommunities().stream()
                .max(Comparator.comparingInt((Set<Long> community) -> longestPathInCommunity(graph, community)))
                .map(community -> community.stream()
                        .map(userRepository::findOne)
                        .sorted(Comparator.comparing(User::getLastName).thenComparing(User::getFirstName))
                        .toList())
                .orElse(List.of());
    }

    /**
     * construieste lista de adiacenta: fiecare utilizator -> lista vecinilor lui;
     * prieteniile cu utilizatori inexistenti sunt ignorate
     *
     * @return graful retelei
     */
    private Map<Long, List<Long>> buildGraph() {
        Set<Long> userIds = userRepository.stream()
                .map(User::getId)
                .collect(Collectors.toSet());

        Map<Long, List<Long>> neighbours = friendshipRepository.stream()
                .filter(f -> userIds.contains(f.getUserId1()) && userIds.contains(f.getUserId2()))
                .flatMap(f -> Stream.of(new Tuple<>(f.getUserId1(), f.getUserId2()),
                        new Tuple<>(f.getUserId2(), f.getUserId1())))
                .collect(Collectors.groupingBy(Tuple::getLeft,
                        Collectors.mapping(Tuple::getRight, Collectors.toList())));

        return userIds.stream()
                .collect(Collectors.toMap(Function.identity(), id -> neighbours.getOrDefault(id, List.of())));
    }

    /**
     * @return comunitatile (componentele conexe), fiecare ca multime de id-uri
     */
    private List<Set<Long>> getCommunities() {
        Map<Long, List<Long>> graph = buildGraph();
        return graph.keySet().stream()
                .map(id -> reachableFrom(id, graph))
                .distinct()
                .toList();
    }

    /**
     * @param start - nodul de pornire
     * @param graph - graful retelei
     * @return toate nodurile la care se poate ajunge din start (comunitatea lui)
     */
    private Set<Long> reachableFrom(Long start, Map<Long, List<Long>> graph) {
        Set<Long> visited = new HashSet<>();
        dfs(start, graph, visited);
        return visited;
    }

    /**
     * parcurgere in adancime; vecinii nevizitati sunt procesati cu stream-uri
     *
     * @param node    - nodul curent
     * @param graph   - graful retelei
     * @param visited - nodurile vizitate pana acum
     */
    private void dfs(Long node, Map<Long, List<Long>> graph, Set<Long> visited) {
        visited.add(node);
        graph.get(node).stream()
                .filter(neighbour -> !visited.contains(neighbour))
                .forEach(neighbour -> dfs(neighbour, graph, visited));
    }

    /**
     * @param graph     - graful retelei
     * @param community - nodurile comunitatii
     * @return lungimea celui mai lung drum simplu din comunitate
     */
    private int longestPathInCommunity(Map<Long, List<Long>> graph, Set<Long> community) {
        return community.stream()
                .mapToInt(start -> longestPathFrom(start, graph, new HashSet<>()))
                .max()
                .orElse(0);
    }

    /**
     * backtracking: cel mai lung drum simplu care porneste din node
     *
     * @param node    - nodul curent
     * @param graph   - graful retelei
     * @param visited - nodurile de pe drumul curent
     * @return lungimea celui mai lung drum care porneste din node
     */
    private int longestPathFrom(Long node, Map<Long, List<Long>> graph, Set<Long> visited) {
        visited.add(node);
        int best = graph.get(node).stream()
                .filter(neighbour -> !visited.contains(neighbour))
                .mapToInt(neighbour -> 1 + longestPathFrom(neighbour, graph, visited))
                .max()
                .orElse(0);
        visited.remove(node);
        return best;
    }
}