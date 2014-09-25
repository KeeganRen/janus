#include <stdlib.h>
#include <string.h>

#include "iarpa_janus.h"
#include "iarpa_janus_io.h"

const char *get_ext(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if (!dot || dot == filename) return "";
	return dot + 1;
}

int main(int argc, char *argv[])
{
    if ((argc < 6) || (argc > 8)) {
        printf("Usage: janus_enroll sdk_path temp_path data_path metadata_file gallery_file [[algorithm] verbose]\n");
        return 1;
    }

    const char *ext1 = get_ext(argv[4]);
    const char *ext2 = get_ext(argv[5]);

    if (strcmp(ext1, "csv") != 0) {
    	printf("metadata_file must be \".csv\" format.\n");
    	return 1;
    }

    if (strcmp(ext2, "gal") != 0) {
    	printf("gallery_file must be \".gal\" format. \n");
    	return 1;
    }

    JANUS_ASSERT(janus_initialize(argv[1], argv[2], argc >= 8 ? argv[7] : ""))
    JANUS_ASSERT(janus_create_gallery(argv[3], argv[4], argv[5], argc >= 8 ? atoi(argv[7]) : 0))
    JANUS_ASSERT(janus_finalize())

    janus_print_metrics(janus_get_metrics());
    return EXIT_SUCCESS;
}
