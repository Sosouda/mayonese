class Spis
{
    protected Elem head;

    Spis()
    {
        head = null;
    }

    void push(String name, int year, float mark)
    {
        Elem elem = new Elem(name, year, mark);

        if (head == null)
            head = elem;
        else
        {
            elem.next = head;
            head = elem;
        }
    }

    void pushSorted(String name, int year, float mark)
    {
        Elem elem = new Elem(name, year, mark);

        if (head == null)
        {
            head = elem;
            return;
        }

        if (head.next == null)
        {
            if (elem.info.name.compareTo(head.info.name) < 0)
            {
                elem.next = head;
                head = elem;
            }
            else
                head.next = elem;

            return;
        }

        Elem curr_elem = head;
        while (curr_elem.next != null)
        {
            if ( elem.info.name.compareTo(curr_elem.info.name) > 0 && elem.info.name.compareTo(curr_elem.next.info.name) <= 0)
            {
                elem.next = curr_elem.next;
                curr_elem.next = elem;
                return;
            }

            curr_elem = curr_elem.next;
        }
        curr_elem.next = elem;

    }

    void print()
    {
        Elem curr_elem = head;
        while (curr_elem != null)
        {
            curr_elem.print();
            curr_elem = curr_elem.next;
        }
        System.out.println();
    }


}

