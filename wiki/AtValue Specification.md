# Specification

## AtValue

### Invariants

1. Root Node has no `parent`.
2. For Root Node `parent_id = 0`.
3. There can be **only one** Root Node.
4. All non-root nodes have **only one** `parent`
5. For each branch of the facility if a component at level n has `active_capacity` then no copmonents on levels N+x can have `active capacity`.  I.e. if capacity is generated at level 1 for a specific branch then all of the subsequent levels shall have an `active_capacity ` of `0`. 


## Component

### Invariants

1. Component associated with root `Node` must have `id`= 1.
2. All `component_id`s `>= 1`.
