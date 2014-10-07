inline void free_resources(void) {
    display         -> destroy(display);
    queue           -> destroy(queue);
}

