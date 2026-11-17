import domain.Grade;
import domain.Homework;
import domain.Student;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    private static List<Student> getStudents() {
        Student s1 = new Student("andrei", 221);
        s1.setId(1L);
        Student s2 = new Student("dan", 222);
        s2.setId(2L);
        Student s3 = new Student("gigi", 221);
        s3.setId(3L);
        Student s4 = new Student("costel", 222);
        s4.setId(4L);
        return Arrays.asList(s1, s2, s3, s4);
    }

    private static List<Homework> getHomeworks() {
        return Arrays.asList(
                new Homework("t1", "desc1"),
                new Homework("t2", "desc2"),
                new Homework("t3", "desc3"),
                new Homework("t4", "desc4")
        );
    }

    private static List<Grade> getGrades(List<Student> stud, List<Homework> homeworks) {
        return Arrays.asList(
                new Grade(stud.get(0), homeworks.get(0), 10d, LocalDate.of(2019, 11, 2), "profesor1"),
				new Grade(stud.get(0), homeworks.get(1), 10d, LocalDate.of(2019, 11, 2), "profesor2"),
                new Grade(stud.get(1), homeworks.get(0), 9d, LocalDate.of(2019, 11, 2).minusWeeks(1), "profesor1"),
                new Grade(stud.get(1), homeworks.get(1), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Grade(stud.get(1), homeworks.get(2), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Grade(stud.get(2), homeworks.get(1), 7d, LocalDate.of(2019, 10, 28), "profesor1"),
                new Grade(stud.get(2), homeworks.get(3), 9d, LocalDate.of(2019, 10, 27), "profesor2"),
                new Grade(stud.get(1), homeworks.get(3), 10d, LocalDate.of(2019, 10, 29), "profesor2")
        );
    }
    public static void raport1(List<Grade> grades, String name) {
        // 1. filtrare dupa conditie
        List<Grade> filteredGrades = grades.stream()
                .filter(g -> g.getStudent().getName().contains(name))
                .collect(Collectors.toList());
        // 2. grupare + media
        Map<String, Double> byAverage = filteredGrades.stream()
                .collect(Collectors.groupingBy(g -> g.getStudent().getName(),
                        Collectors.averagingDouble(g -> g.getValue())));
        // 3. sortare descrescatoare dupa medie
        byAverage.entrySet().stream()
                .sorted((a, b) -> Double.compare(b.getValue(), a.getValue()))
                .forEach(e -> System.out.println("Student: " + e.getKey() + " average: " + e.getValue()));
    }

    public static void raport2(List<Grade> grades, String name) {
        List<Grade> filteredGrades = grades.stream()
                .filter(g -> g.getTeacher().contains(name))
                .collect(Collectors.toList());
        Map<String, Double> byAverage = filteredGrades.stream()
                .collect(Collectors.groupingBy(g -> g.getTeacher(),
                        Collectors.averagingDouble(g -> g.getValue())));
        byAverage.entrySet().stream()
                .sorted((a, b) -> Double.compare(b.getValue(), a.getValue()))
                .forEach(e -> System.out.println("Teacher: " + e.getKey() + " average: " + e.getValue()));
    }

    public static void raport3(List<Grade> grades, int group) {
        List<Grade> filteredGrades = grades.stream()
                .filter(g -> g.getStudent().getGroup() == group)
                .collect(Collectors.toList());

        Map<String, Long> byCount = filteredGrades.stream()
                .collect(Collectors.groupingBy(g->g.getHomework().getId(), Collectors.counting()));

        byCount.entrySet().stream()
                .sorted((a, b) -> Long.compare(b.getValue(), a.getValue()))
                .forEach(e -> System.out.println("Homework: " + e.getKey() + " nr of students: " + e.getValue()));
    }

    public static void raport4(List<Grade> grades, String prefix) {
        // 1. filtrare: doar notele studentilor din grupe care incep cu prefix
        List<Grade> filteredGrades = grades.stream()
                .filter(g -> String.valueOf(g.getStudent().getGroup()).startsWith(prefix))
                .collect(Collectors.toList());
        // 2. gruparea dupa grupa + medie
        Map<Integer, Double> byAverage = filteredGrades.stream()
                .collect(Collectors.groupingBy(g->g.getStudent().getGroup(), Collectors.averagingDouble(g -> g.getValue())));

        // 3. sortarea descrescatoare dupa medie
        byAverage.entrySet().stream()
                .sorted((a, b) -> Double.compare(b.getValue(), a.getValue()))
                .forEach(e -> System.out.println("Group: " + e.getKey() + " average: " + e.getValue()));
    }

    public static void raport5(List<Grade> grades, List<Student> students){
        //1. cati studenti are fiecare grupa
        Map<Integer, Long> studentsPerGroup = students.stream()
                .collect(Collectors.groupingBy(s->s.getGroup(), Collectors.counting()));
        //2. suma notelor de pe fiecare grupa
        Map<Integer, Double> sumPerGroup = grades.stream()
                .collect(Collectors.groupingBy(g->g.getStudent().getGroup(), Collectors.summingDouble(g -> g.getValue())));

        //3. media = sumaNotelor/nr de studenti
        Map<Integer, Double> byAverage = studentsPerGroup.entrySet().stream()
                .collect(Collectors.toMap(e->e.getKey(),
                        e->sumPerGroup.getOrDefault(e.getKey(), 0.0)/e.getValue()));

        //4. sortarea descrescatoare dupa medie
        byAverage.entrySet().stream()
                .sorted((a, b) -> Double.compare(b.getValue(), a.getValue()))
                .forEach(e -> System.out.println("Group: " + e.getKey() + " average: " + e.getValue()));
    }


    public static void main(String[] args) {
        List<Grade> grades = getGrades(getStudents(), getHomeworks());
        grades.forEach(System.out::println);

        System.out.println("\n--- Raport 1 ---");
        raport1(grades, "a");

        System.out.println("\n--- Raport 2 ---");
        raport2(grades, "profesor");

        System.out.println("\n--- Raport 3 ---");
        raport3(grades, 221);

        System.out.println("\n--- Raport 4 ---");
        raport4(grades, "22");

        System.out.println("\n--- Raport 4 ---");
        raport5(grades, getStudents());

    }
}