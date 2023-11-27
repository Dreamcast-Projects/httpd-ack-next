#include "common.h"

void send_sd(http_state_t *hs) {
    /* Set up stream for webpage content */
    char *output;
    size_t output_size = 0;
    FILE *page = open_memstream(&output, &output_size);
    if(!page) {
        send_error(hs, 404, "Could not create new buffer for page");
        conio_printf("Error %d when creating buffer for socket %d\n", errno, hs->socket);
        return;
    }

    /* Write webpage content to stream */
    fprintf(page, "<html><head>");
    fprintf(page, stylesheet);
    fprintf(page, "<title>Dream Web Console - SD Management</title></head></html>\n<body>\n");
    fprintf(page, "<h1>Dream Web Console - SD Management</h1>\n");
    fprintf(page, "<p>The SD management page is currently unimplemented. Come back later for more.</p>\n");
    fprintf(page, html_footer);

    /* Write output to socket */
    fclose(page);
    send_ok(hs, "text/html", -1);
    char *cursor = output;
    while(output_size > 0) {
        int rv = write(hs->socket, cursor, output_size);
        if (rv <= 0)
            goto send_out;
        output_size -= rv;
        cursor += rv;
    }
    send_out:
    free(output);
    output = NULL;
}
