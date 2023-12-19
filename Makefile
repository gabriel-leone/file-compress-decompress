compactador: compactador.c compress.c compress.h building.c building.h tree.c tree.h queue.c queue.h
	gcc compactador.c compress.c compress.h building.c building.h tree.c tree.h queue.c queue.h -o compactador

descompactador: descompactador.c decompress.c decompress.h building.c building.h tree.c tree.h queue.c queue.h
	gcc descompactador.c decompress.c decompress.h building.c building.h tree.c tree.h queue.c queue.h -o descompactador