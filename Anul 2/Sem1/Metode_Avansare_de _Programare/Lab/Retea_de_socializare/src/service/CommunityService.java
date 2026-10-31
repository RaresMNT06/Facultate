package service;

import model.Friendship;
import model.Tuple;
import model.User;
import repository.Repository;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Operatii pe reteaua vazuta ca graf: utilizatorii sunt noduri, prieteniile sunt muchii.
 */
public class CommunityService {

    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;

    /**
     * @param userRepository       repository-ul de utilizatori
     * @param friendshipRepository repository-ul de prietenii
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
     * Comunitatea cea mai sociabila este cea care contine cel mai lung drum.
     *
     * @return utilizatorii din comunitatea cea mai sociabila (lista goala daca nu exista utilizatori)
     */
    public List<User> getMostSociableCommunity(){
        Map<Long, List<Long>> graph = buildGraph();
        List<Long> bestCommunity = new ArrayList<>();
        int bestLength = -1;

        for (List<Long> community : getCommunities()){
            int length = longestPathInCommunity(graph, community);
            if (length > bestLength){
                bestLength = length;
                bestCommunity = community;
            }
        }

        List<User> users = new ArrayList<>();
        for (Long id : bestCommunity){
            users.add(userRepository.findOne(id));
        }
        return users;
    }

    // Pasul 1: lista de adiacenta
    private Map<Long, List<Long>> buildGraph(){
        Map<Long, List<Long>> graph = new HashMap<>();
        for (User user : userRepository.findAll()){
            graph.put(user.getId(), new ArrayList<>());
        }
        for (Friendship friendship : friendshipRepository.findAll()){
            Long id1 = friendship.getUserId1();
            Long id2 = friendship.getUserId2();
            if(graph.containsKey(id1) && graph.containsKey(id2)) {
                graph.get(id1).add(id2);
                graph.get(id2).add(id1);
            }
        }
        return graph;
    }

    // Pasul 2: componentele conexe cu DFS
    private List<List<Long>> getCommunities(){
        Map<Long, List<Long>> graph = buildGraph();
        Set<Long> visited = new HashSet<>();
        List<List<Long>> communities = new ArrayList<>();

        for (Long node : graph.keySet()){
            if (!visited.contains(node)){
                List<Long> community = new ArrayList<>();
                dfs(node, graph, visited, community);
                communities.add(community);
            }
        }
        return communities;
    }

    private void dfs(Long node, Map<Long, List<Long>> graph, Set<Long> visited, List<Long> community){
        visited.add(node);
        community.add(node);
        for (Long neighbor : graph.get(node)){
            if (!visited.contains(neighbor)){
                dfs(neighbor, graph, visited, community);
            }
        }
    }

    // Pasul 3: cel mai lung drum dintr-o comunitate
    private int longestPathInCommunity(Map<Long, List<Long>> graph, List<Long> community){
        int best = 0;
        for (Long start: community){
            int length = longestPathFrom(start, graph, new HashSet<>());
            if (length > best){
                best = length;
            }
        }
        return best;
    }

    private int longestPathFrom(Long node, Map<Long, List<Long>> graph, Set<Long> visited){
        visited.add(node);
        int best = 0;
        for (Long neighbor : graph.get(node)){
            if (!visited.contains(neighbor)){
                int length =  1 + longestPathFrom(neighbor, graph, visited);
                if (length > best){
                    best = length;
                }
            }
        }
        visited.remove(node);
        return best;
    }

}
