public class Deck extends Spis {
    public void pushFront(Elem data) {
        Node newNode = new Node(data);
        if (head == null) {
            head = newNode;
        } else {
            newNode.next = head;
            head = newNode;
        }
    }

    public void popFront() {
        if (head != null) {
            head = head.next;
        }
    }

    public void pushBack(Elem data) {
        super.push(data);
    }

    public void popBack() {
        if (head == null) {
            return;
        } else if (head.next == null) {
            head = null;
        } else {
            Node current = head;
            while (current.next.next != null) {
                current = current.next;
            }
            current.next = null;
        }
    }

    public void printListFront() {
        super.printList();
    }

    public void printListBack() {
        Node current = head;
        Node prev = null;
        Node next;
        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        head = prev;
        super.printList();
    }
}