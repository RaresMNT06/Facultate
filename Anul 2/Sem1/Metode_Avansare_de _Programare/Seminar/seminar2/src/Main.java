import model.Student;

import java.util.*;

import model.MyMap;

public class Main {

    public static void main(String[] args) {

        // ===== Cerinta 1: Clasa Student =====
        System.out.println("===== Cerinta 1 =====");
        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);
        System.out.println(s1.equals(s3));

        // ===== Cerinta 2 + 3: HashSet + contractul equals/hashCode =====
        System.out.println("\n===== Cerinta 2 + 3 =====");
        Set<Student> students = new HashSet<>();
        students.add(s1);
        students.add(s2);
        students.add(s3);
        System.out.println("HashSet: " + students);

        // ===== Cerinta 4: TreeSet cu comparator dupa nume =====
        System.out.println("\n===== Cerinta 4 (comparator dupa nume) =====");
        Comparator<Student> byName = new Comparator<Student>() {
            @Override
            public int compare(Student a, Student b) {
                return a.getName().compareTo(b.getName());
            }
        };

        Set<Student> treeSet = new TreeSet<>(byName);
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);
        System.out.println("TreeSet: " + treeSet);

        // ===== Cerinta 4: TreeSet cu comparator dupa medie =====
        System.out.println("\n===== Cerinta 4 (comparator dupa medie) =====");
        Comparator<Student>averageComparator = new Comparator<Student>() {
            @Override
            public int compare(Student a, Student b) {
                return Float.compare(a.getAverage(), b.getAverage());
            }
        };

        Set<Student> setWithComparator = new TreeSet<>(averageComparator);
        setWithComparator.add(s1);
        setWithComparator.add(s2);
        setWithComparator.add(s3);
        for(Student student : setWithComparator){
            System.out.println(student);
        }

        // ===== Cerinta 5: HashMap =====
        System.out.println("\n===== Cerinta 5 (HashMap) =====");
        Map<String, Student> map = new HashMap<>();
        map.put(s1.getName(), s1);
        map.put(s2.getName(), s2);
        map.put(s3.getName(), s3);
        for(Map.Entry<String, Student> entry : map.entrySet()){
            System.out.println("Key: "+entry.getKey());
            System.out.println("Value: "+entry.getValue());
        }

        // ===== Cerinta 5: TreeMap =====
        System.out.println("\n===== Cerinta 5 (TreeMap) =====");
        Map<String, Student> treeMap = new TreeMap<>();
        treeMap.put(s1.getName(), s1);
        treeMap.put(s2.getName(), s2);
        treeMap.put(s3.getName(), s3);
        for(Map.Entry<String, Student> entry : treeMap.entrySet()){
            System.out.println("Key: "+entry.getKey());
            System.out.println("Value: "+entry.getValue());
        }


        // ===== Cerinta 6: MyMap =====
        System.out.println("\n===== Cerinta 6 (MyMap) =====");
        MyMap myMap = new MyMap();
        for (Student student : getList()) {
            myMap.add(student);
        }

        for (Map.Entry<Integer, List<Student>> entry : myMap.getEntries()) {
            entry.getValue().sort(byName);
            System.out.println("Media " + entry.getKey() + ": " + entry.getValue());
        }



        System.out.println("\n===== Iterator =====");
        Iterator<Student> iterator = getList().iterator();
        while(iterator.hasNext()){
            System.out.println(iterator.next());
        }




    }
    public static List<Student> getList() {
        List<Student> l = new ArrayList<Student>();
        l.add(new Student("1", 9.7f));
        l.add(new Student("2", 7.3f));
        l.add(new Student("3", 6f));
        l.add(new Student("4", 6.9f));
        l.add(new Student("5", 9.5f));
        l.add(new Student("6", 9.9f));
        return l;
    }
}
