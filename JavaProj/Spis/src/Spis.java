public class Spis{
    protected Node head;

    protected static class Elem{
        int data;

        public void print() {
            System.out.println(data);
        }

        @Override
        public String toString() {
            return String.valueOf(data);
        }
    }
    protected static class Node {
        Elem data;
        Node next;

        public Node(Elem data) {
            this.data = data;
            this.next = null;
        }
    }
    public void push(Elem data) {
        Node newNode = new Node(data);
        if (head == null) {
            head = newNode;
        } else {
            Node current = head;
            while (current.next != null) {
                current = current.next;
            }
            current.next = newNode;
        }
    }

    public void printList() {
        Node current = head;
        while (current != null) {
            System.out.print(current.data + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }
}

