public class SinglyLinkedList {
    static class LinkedList {
        static class Node {
            int val;
            Node next;

            Node(int val) {
                this.val = val;
                this.next = null;
            }
        }

        private Node head;

        public void insertFirst(int val) {
            Node n = new Node(val);
            n.next = head;
            head = n;
        }

        public void insertLast(int val) {
            Node curr = head;
            while (curr.next != null) {
                curr = curr.next;
            }

            Node n = new Node(val);
            curr.next = n;
        }

        public void print() {
            Node curr = head;
            while (curr != null) {
                System.out.print(curr.val);
                if (curr.next != null)
                    System.out.print(" -> ");
                curr = curr.next;
            }
            System.out.println(" (END)");
        }

        public boolean find(int target) {
            for (Node curr = head; curr.next != null; curr = curr.next) {
                if (curr.val == target) return true;
            }
            return false;
        }

        public void delete(int val) {
            if (head == null) return;

            if (head.val == val) {
                head = head.next;
                return;
            }

            Node curr = head;
            while (curr.next != null && curr.next.val != val) {
                curr = curr.next;
            }

            // found the value, change the pointer of the current to the 2 nodes ahead
            // we dont really "delete" the value, just remove it from the chain
            if (curr.next != null) {
                curr.next = curr.next.next;
            }
        }
    }


    public static void main(String[] args) {
        LinkedList list = new LinkedList();

        list.insertFirst(3);
        list.insertFirst(1);
        list.insertFirst(8);

        list.insertLast(9);
        list.insertLast(2);
        list.insertLast(5);

        list.print();

        System.out.println(list.find(99));
        System.out.println(list.find(9));

        list.delete((3));
        list.print();
    }
}