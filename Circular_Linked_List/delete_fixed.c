bool delete_elem_by_value(LinkList head, ElemType e) {
    if (is_empty(head)) {
        return false;
    }

    Node* prev = head;
    Node* curr = head->next;
    bool deleted = false;

    while (curr != head) {
        if (curr->e == e) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
            deleted = true;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return deleted;
}