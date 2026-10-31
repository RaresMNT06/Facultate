package ex.functional;

public class G11 {

    private final String  name= "G11";

    void run(){
        Runnable anonymous = new Runnable() {
            private final String name = "anonima";
            @Override
            public void run() {
                System.out.println(this.name);
            }
        };
        Runnable lambda = ()-> System.out.println(this.name);
        anonymous.run();
        lambda.run();
    }

    public static void main(String[] args) {
        new G11().run();
    }
}
