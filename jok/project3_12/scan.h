#ifndef _SCAN_H_ 
#define _SCAN_H_ 

/* Maximum length of token */ 
#define MAXTOKENLEN 40 

/*
 * lexeme
 * defined in cm.l
 */
extern char tokenString[MAXTOKENLEN+1]; 
extern char tokenBefore[MAXTOKENLEN+1];

/*
 * read one token
 * return TokenType
 * set tokenString and tokenBefore
 */
TokenType getToken(void); 
 
#endif 

