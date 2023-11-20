public class Stack extends Spis {
    public Elem pop() {
        if (head == null) {
            throw new IllegalStateException("Stack is empty");
        }
        Elem data = head.data;
        head = head.next;
        return data;

    }
}

