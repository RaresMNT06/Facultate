package domain;

import util.Constants;

import java.time.LocalDate;

public class Grade {
    private Student student;
    private Homework homework;
    private double value;
    private LocalDate date;
    private String teacher;

    public Grade(Student student, Homework homework, double value, LocalDate date, String teacher) {
        this.student = student;
        this.homework = homework;
        this.value = value;
        this.date = date;
        this.teacher = teacher;
    }

    public Student getStudent() {
        return student;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public Homework getHomework() {
        return homework;
    }

    public void setHomework(Homework homework) {
        this.homework = homework;
    }

    public double getValue() {
        return value;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public String getTeacher() {
        return teacher;
    }

    public void setTeacher(String teacher) {
        this.teacher = teacher;
    }

    @Override
    public String toString() {
        return "Grade{" +
                "student=" + student +
                ", homework=" + homework +
                ", value=" + value +
                ", date=" + date.format(Constants.DATE_FORMATTER) +
                ", teacher='" + teacher + '\'' +
                '}';
    }
}
