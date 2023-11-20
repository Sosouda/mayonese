public class Elem{
    Node info;
    Elem next;

    Elem(String name, int year, float mark)
    {
        this.info = new Node(name, year, mark);
        this.next = null;
    }

    public void print()
    {
        info.print();
    }

}
