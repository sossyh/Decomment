#include<stdio.h>
#include<ctype.h>
#include <stdbool.h>
#include<stdlib.h>
#define EXIT_SUCCESS 0
#define EXIT_FALIURE -1

/* this de-commenting is used to uncomment the set of characters */

typedef enum {
	NORMAL,
	SLASH,          // encountered opening '/'
    QUOTE,
	END_OF_QUOTE,	// encountered " and '
	STAR,	        // encountered closing '*'
	IN_COMMENT,    //accepting the comment within / * * / 	    
	END_COMMENT,	
} state;

/*Is a state whenever there is no comment existed*/
void normal_state_operant(state *state, char input_char){
	if(input_char=='/'){
		*state = SLASH;
	}
	else if(input_char=='"' || input_char=='\''){
		putchar(input_char);
		*state = QUOTE;
	}
	else if(input_char=='\\'){
		*state=NORMAL;
	}
	else if(*state==NORMAL && input_char=='n'){
		printf("\n");
	}
	else{
		putchar(input_char);
	}
	

};
/*Is a state that will be achieved when a slash character is encountered*/
void slash_state_operant(state *state, char input_char){
	if(input_char=='*'){
		putchar(' ');
		*state = IN_COMMENT;
	}
	else{
		putchar('/');
		if(input_char=='/'){
		putchar(input_char);
		*state=NORMAL;
		}
		else{
		putchar(input_char);
		*state=NORMAL;
		}
	}
	
};
/*comment state handeler fuction which even sets the comment line*/
void in_comment_state_operant(state *state, char input_char, int *commentStartLine,int *currentLine){
	if(input_char=='*'){
		*state = STAR;
	}
	else if(input_char=='\\'){
		*state=IN_COMMENT;
	}
	else if(*state==IN_COMMENT && input_char=='n'){
		printf("\n");
	}
	else{
		*state = IN_COMMENT;
		*commentStartLine= *currentLine;
	}
	
};
/*Is a state that will be achieved when a star character is encountered*/
void star_state_operant(state *state, char input_char){
	if(input_char=='/'){
			*state = END_COMMENT;
		}
	else if(input_char=='*'){
			*state = STAR;
		}
	else{
		*state = IN_COMMENT;
	}
};
void end_comment_state_operant(state *state, char input_char){
	putchar(input_char);
	*state= NORMAL;
	
};
/*Is a state that will be achieved when a quote character is encountered*/
void quote_state_operant(state *state, char input_char){
	if(input_char=='"'){
		putchar(input_char);
		*state=END_OF_QUOTE;
	}
	else{
		putchar(input_char);
	}
};

void end_of_quote_state_operant(state *state, char input_char){
	*state=NORMAL;
};
/*A function which check the completing status i.e whether it is in accepting or rejecting state*/
void comment_completed(state *state, int commentEndLine)
{
	if (*state == IN_COMMENT || *state == END_COMMENT) {
        fprintf(stderr, "Error: line  %d  is unterminated comment.\n", commentEndLine );
		exit(EXIT_FALIURE);
    }
	else{
		exit(EXIT_SUCCESS);
	}
};
/*A function which counts the number of lines from the inserted characters*/
void LineNumber(int *line, char input_char) {

    if (input_char == '\n') {
        *line += 1;
    }
}
int main(){
	char input_char;
	state state=NORMAL;
	int line = 0;  
    int commentStartLine = 1;
	int commentEndLine;
	int currentLine;

	while (true)
	 
	{
		char input_char = getchar();
        LineNumber(&line, input_char);
		if(input_char==EOF)
		{
			comment_completed(&state,input_char);
			break;
		}
		/*calling the operator functions in thier respective state*/
		if(state==NORMAL){
			normal_state_operant(&state, input_char);
		}
		else if(state==SLASH){
			slash_state_operant(&state, input_char);
		}
		else if(state==QUOTE){
			quote_state_operant(&state, input_char);
		}
		else if(state==IN_COMMENT){
			in_comment_state_operant(&state, input_char,&commentStartLine,&line);
		}
		else if(state==STAR){
			star_state_operant(&state, input_char);
		}
		else if(state==END_OF_QUOTE){
			end_of_quote_state_operant(&state, input_char);
		}
		else if (state==END_COMMENT){
			end_comment_state_operant(&state, input_char);
		}

	}
	
    return 0;
};
