public class Queue extends Spis {

    public void pushtail(Elem data) {
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


    public Elem poptail() {
        if (head == null) {
            throw new IllegalStateException("Queue is empty");
        }
        Elem data = head.data;
        head = head.next;
        return data;
    }

}