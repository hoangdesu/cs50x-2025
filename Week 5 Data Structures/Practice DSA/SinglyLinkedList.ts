// interface SinglyLinkedList<T> {
//     get length(): number;
//     append(item: T): void;
//     prepend(item: T): void;
//     print(): void;
// }

type Node<T> = {
    value: T,
    next?: Node<T>,
}

export default class SinglyLinkedList<T> {
    public length: number;
    private head?: Node<T>;

    constructor() {
        this.length = 0;
    }

    prepend(item: T): void {
        const n: Node<T> = {
            value: item,
            next: undefined,
        }

        n.next = this.head;
        this.head = n;

        this.length++;
    }

    append(item: T): void {
        let n = this.head;
        while (n?.next !== undefined) {
            n = n.next;
        }
        // console.log('n=', n?.value, n?.next);
        const newNode: Node<T> = {
            value: item,
            next: undefined
        }
        n.next = newNode;

        this.length++;
    }

    get(index: number): T | undefined {
        if (index > this.length - 1) return undefined;

        let n = this.head;
        let ctr = 0
        while (index !== ctr && n !== undefined) {
            n = n?.next;
            ctr++;
        }

        return n?.value;
    }

    remove(item: T): T | undefined {
        // special case: removing the head
        if (this.head?.value === item) {
            this.head = this.head.next;
        }

        // traverse through the list to find the element to remove
        let ptr = this.head;
        while (ptr?.next !== undefined) {
            if (ptr?.next?.value === item) {
                // console.log('found:', item);
                const removed = ptr.next.value;
                ptr.next = ptr.next.next;
                this.length--;
                return removed;
            }
            // console.log('current ptr:', ptr?.value, ptr?.next?.value, item);
            
            ptr = ptr.next;
        }

        // console.log('ptr:', ptr?.value, ptr?.next);

        return undefined;
    }

    print(): void {
        console.log('length = ', this.length);
        let n = this.head;
        while (n !== undefined) {
            console.log(n.value);
            n = n.next;
        }

    }
}


// main
const list = new SinglyLinkedList();

list.prepend(2);
list.prepend(3);
list.prepend(1);

list.append(8);
list.append(6);

list.print();

console.log('get list[3] =', list.get(3)); // 8

console.log('removed 8:', list.remove(8));
console.log('removed 11:', list.remove(11));

list.print();


