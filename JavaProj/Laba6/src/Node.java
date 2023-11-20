public class Node {
    String name;
    int year;
    float mark;

    Node(String name, int year, float mark)
    {
        this.name = name;
        this.year = year;
        this.mark = mark;
    }

    public void print()
    {
        System.out.println("Name: " + name + ", year: " + year + ", mark: " + mark + ". " );
    }
}
