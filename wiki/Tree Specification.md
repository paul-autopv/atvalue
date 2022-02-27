# Specification

## AtValue

### Invariants

1. Root Node has no `parent`.
2. For Root Node `parent_id = 0`.
3. There can be **only one** Root Node.
4. All non-root nodes have **only one** `parent`


## Component

### Invariants

1. Component associated with root `Node` must have `id`= 1.
2. All `component_id`s `>= 1`.
