public class Class1 {
    static int stop = 3;
    public static void main(String args[]){
        System.out.println("I'm main() from class 1");
        Class1.stop -= 1;
        if(Class1.stop >0){
        Class2.main(args);}
    }
}
