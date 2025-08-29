"use strict";
// interface SinglyLinkedList<T> {
//     get length(): number;
//     append(item: T): void;
//     prepend(item: T): void;
//     print(): void;
// }
Object.defineProperty(exports, "__esModule", { value: true });
var SinglyLinkedList = /** @class */ (function () {
    function SinglyLinkedList() {
        this.length = 0;
    }
    SinglyLinkedList.prototype.prepend = function (item) {
        var n = {
            value: item,
            next: undefined,
        };
        n.next = this.head;
        this.head = n;
        this.length++;
    };
    SinglyLinkedList.prototype.append = function (item) {
        var n = this.head;
        while ((n === null || n === void 0 ? void 0 : n.next) !== undefined) {
            n = n.next;
        }
        // console.log('n=', n?.value, n?.next);
        var newNode = {
            value: item,
            next: undefined
        };
        n.next = newNode;
        this.length++;
    };
    SinglyLinkedList.prototype.get = function (index) {
        if (index >= this.length - 1)
            return undefined;
        var n = this.head;
        var ctr = 0;
        while (index !== ctr) {
            n = n === null || n === void 0 ? void 0 : n.next;
            ctr++;
        }
        return n === null || n === void 0 ? void 0 : n.value;
    };
    SinglyLinkedList.prototype.print = function () {
        console.log('length = ', this.length);
        var n = this.head;
        while (n !== undefined) {
            console.log(n.value);
            n = n.next;
        }
    };
    return SinglyLinkedList;
}());
exports.default = SinglyLinkedList;
var list = new SinglyLinkedList();
list.prepend(2);
list.prepend(3);
list.prepend(1);
list.append(5);
list.print();
console.log('get:', list.get(2)); // 5
