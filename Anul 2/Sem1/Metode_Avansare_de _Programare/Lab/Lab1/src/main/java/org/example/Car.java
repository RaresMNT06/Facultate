package org.example;

public class Car {
    private int year;
    private double price;

    public Car(int year, double price){
        this.year =year;
        this.price = price;
    }
    public int getyear(){
        return year;
    }
    public double getprice(){
        return price;
    }
    public String toString(){
        return "price: "+ price + " year: " +year;
    }

}





