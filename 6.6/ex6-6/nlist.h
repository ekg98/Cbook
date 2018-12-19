// nlist.h:  Contains structure definition for nlist structure

struct nlist{			// table entry
	struct nlist *next;	// next entry in chain
	char *name;		// defined name
	char *defn;		// replacement text
};
