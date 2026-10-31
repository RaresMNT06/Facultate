package model;

import java.util.Objects;

public class Student {

    private String name;
    private float average;

    public Student(String name, float average) {
        this.name = name;
        this.average = average;
    }

    public String getName() {
        return name;
    }

    public float getAverage() {
        return average;
    }

    @Override
    public String toString() {
        return "Student [name=" + name + ", average=" + average + "]";
    }

    // Cerinta 3: contractul equals - hashCode
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Student)) return false;
        Student student = (Student) o;
        return Float.compare(average, student.average) == 0 && Objects.equals(name, student.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, average);
    }
}