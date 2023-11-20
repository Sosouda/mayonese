public class Main {
    public static void main(String[] args) {

        Spis spis = new Spis();
        Spis.Elem elem1 = new Spis.Elem();
        Spis.Elem elem2 = new Spis.Elem();
        Spis.Elem elem3 = new Spis.Elem();
        elem1.data = 1;
        elem2.data = 2;
        elem3.data = 3;
        spis.push(elem1);
        spis.push(elem2);
        spis.push(elem3);
        System.out.println("Spis:");
        spis.printList();

        Stack stack = new Stack();
        Spis.Elem elem4 = new Spis.Elem();
        Spis.Elem elem5 = new Spis.Elem();
        Spis.Elem elem6 = new Spis.Elem();
        elem4.data = 4;
        elem5.data = 5;
        elem6.data = 6;
        stack.push(elem4);
        stack.push(elem5);
        stack.push(elem6);
        System.out.println("Stack:");
        stack.printList();

        Spis.Elem poppedItem = stack.pop();
        System.out.println("Удалено из Stack: " + poppedItem);
        System.out.println("Обновленный Stack:");
        stack.printList();

        Queue queue = new Queue();
        queue.pushtail(elem1);
        queue.pushtail(elem2);
        queue.pushtail(elem3);

        System.out.println("Queue:");
        queue.printList();

        Spis.Elem item = queue.poptail();
        System.out.println("Удалено: " + item);
        queue.pushtail(elem5);
        System.out.println("Теперь Queue:");
        queue.printList();

        Deck deque = new Deck();
        Spis.Elem elem10 = new Spis.Elem();
        Spis.Elem elem15 = new Spis.Elem();
        Spis.Elem elem20 = new Spis.Elem();
        elem10.data = 10;
        elem15.data = 15;
        elem20.data = 20;
        deque.pushFront(elem5);
        deque.pushFront(elem10);
        deque.pushBack(elem15);
        deque.pushBack(elem20);

        System.out.println("Deck:");
        deque.printListFront();

        deque.popFront();
        deque.popBack();

        deque.printListFront();

        deque.printListBack();

        deque.popFront();
        deque.popBack();

        deque.printListFront();
    }

}