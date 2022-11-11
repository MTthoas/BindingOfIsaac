#ifndef MYSTRING_H

    #define MYSTRING_H

        /**
         * @brief Comme strcpy mais retourne le résultat au lieu 
         * de modifier une variable passée en paramètre.
         * 
         * Ainsi, on est sûrs que la chaîne copiée a bien un espace
         * dédié pour notre programme. 
         * 
         * @return char* 
         */
        char* duplicateString(char*  );

        /**
         * @brief Met la chaine de caractère en majuscule
         * 
         * @param string 
         */
        void uppercase(char string[255]);

#endif