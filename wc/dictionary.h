typedef struct dictionary {
	void (*add_word)(struct dictionary *this, char *word);
	int (*count_word)(struct dictionary *this, char *word);
} dictionary;
