package model;

import java.util.*;
public class MyMap {
    private Map<Integer,List<Student>> map = new TreeMap<>(new DescendingComparator());

    private static class DescendingComparator implements Comparator<Integer> {
        @Override
        public int compare(Integer  o1, Integer o2 ) {
            return o1.compareTo(o2);
        }
    }

    public void add(Student student) {
        int key = Math.round(student.getAverage());
        List<Student> list = map.get(key);
        if (list == null) {
            list = new ArrayList<>();
            map.put(key, list);
        }
        list.add(student);
    }

    public Set<Map.Entry<Integer,List<Student>>> getEntries() {
        return map.entrySet();
    }

}
