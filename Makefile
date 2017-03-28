##
## Makefile for the_sh in .
##
## Made by Nicolas Goudal
## Login   <nicolas.goudal@epitech.eu>
##
## Started on  Thu Mar 02 16:54:25 2017 Nicolas Goudal
## Last update Tue Mar 28 19:30:18 2017 Benoit Hamon
##

CC		=	gcc
RM		=	rm -rf
MAKE		=	make --no-print-directory

SRCS_DIR	=	sources/
OBJS_DIR	=	objects/

HDRS_DIRS	=	headers/
HDRS_DIRS	+=	$(foreach var, $(SUBMODULES), $(var)/headers_public/)

FLAGS_DB	=	-g3

NAME		=	$(shell $(call function, name:, 0))
FLAGS		=	$(addprefix -, $(shell $(call function, flags:, 0)))
LIB		=	$(addprefix -l, $(shell $(call function, libs:, 0)))
SUBMODULES	=	$(shell $(call function, submodules:, 0))
BONUS_FILES	=	$(addprefix $(SRCS_DIR), $(shell $(call function, bonus:, 0)))
SRCS_NAMES	=	$(shell $(call function, \[*\], 1))

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS_NAMES:.c=.o))
OBJS_DEP	=	$(addprefix $(OBJS_DIR), $(SRCS_NAMES:.c=.d))
OBJS_DB		=	$(addprefix $(OBJS_DIR), $(SRCS_NAMES:.c=.db.o))
OBJS_DB_DEP	=	$(addprefix $(OBJS_DIR), $(SRCS_NAMES:.c=.db.d))
HDRS		=	$(addprefix -I, $(HDRS_DIRS))
NAME_DB		=	$(addsuffix _db, $(NAME))
STATIC_LIB	=	$(foreach var, $(SUBMODULES), $(var)/$(addsuffix .a, $(var)))

RED		=	\033[0;31m
GREEN		=	\033[0;32m
BLUE		=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN		=	\033[0;36m
BOLD		=	\033[1m
RESET		=	\033[0m

function = echo $$(while read line ; do                                  \
	     if [[ $$line =~ $1 ]] ; then                                \
	       folder=$$(echo "$$line" | sed 's/\]$$//' | sed 's/^\[//') ; \
	       while read line && [[ ! -z "$$line" ]]; do                \
	         if [ $2 = 1 ] ; then                                    \
	           echo "$$folder/$$line " ;                             \
	         else                                                    \
	           echo "$$line " ;                                      \
	         fi ;                                                    \
	       done ;                                                    \
	     fi ;                                                        \
	   done < .makeconfig)

submodules = $(foreach var, $(SUBMODULES), $(MAKE) $1 -C $(var) ;)

the_clean = $(foreach var, $1, if [ -f $(var) ] ; then                     \
	          printf "   $(RED)[DELETING]$(RESET)\t$(notdir $(var))\n" \
	          && $(RM) $(var) ;                                        \
	        fi ; if [ -d $(var) ] ; then                               \
	          printf "   $(RED)[DELETING]$(RESET)\t$(var)\n"           \
	          && $(RM) $(var) ;                                        \
	        fi ; )

.PHONY : all project debug bonus bonus_db clean fclean re

all : project

project :
	@$(call submodules)
	@printf "\n$(BLUE)$(BOLD)----- PROJECT COMPILATION -----$(RESET)\n"
	@mkdir -p $(OBJS_DIR)
	@if ! $(MAKE) -q $(NAME) ; then                                              \
	    $(MAKE) $(NAME)                                                          \
	    && printf "\n    $(CYAN)$(BOLD)~ COMPILATION COMPLETE ~$(RESET)\n\n" ;   \
	  else                                                                       \
	    printf " Nothing $(GREEN)to do$(RESET) for $(CYAN)$(NAME)$(RESET)\n\n" ; \
	  fi ;

debug :
	@$(call submodules, debug)
	@printf "\n$(BLUE)$(BOLD)--- PROJECT_DB COMPILATION ---$(RESET)\n"
	@mkdir -p $(OBJS_DIR)
	@if ! $(MAKE) -q $(NAME_DB) ; then                                            \
	    $(MAKE) $(NAME_DB)                                                        \
	    && printf "\n    $(CYAN)$(BOLD)~ COMPILATION COMPLETE ~$(RESET)\n\n" ;    \
	else                                                                          \
	  printf " Nothing $(GREEN)to do$(RESET) for $(CYAN)$(NAME_DB)$(RESET)\n\n" ; \
	  fi ;

bonus :
	@$(foreach var, $(BONUS_FILES:.c=.o), $(RM) $(OBJS_DIR)/$(var))
	@$(MAKE) FLAGS_BONUS="-D BONUS"

bonus_db :
	@$(MAKE) debug FLAGS_BONUS="-D BONUS"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@printf "   $(PURPLE)[COMPILING]$(RESET)\t$(notdir $<)\n"
	@-mkdir -p $(dir $@) 2>/dev/null
	@$(CC) -c $< -o $@ $(FLAGS) $(FLAGS_BONUS) $(HDRS)

$(OBJS_DIR)%.db.o : $(SRCS_DIR)%.c
	@printf "   $(PURPLE)[COMPILING]$(RESET)\t$(notdir $<)\n"
	@-mkdir -p $(dir $@) 2>/dev/null
	@$(CC) -c $< -o $@ $(FLAGS) $(FLAGS_DB) $(FLAGS_BONUS) $(HDRS)

$(OBJS_DIR)%.d : $(SRCS_DIR)%.c
	@printf "   $(PURPLE)[INDEXING]$(RESET)\t$(notdir $@)\n"
	@-mkdir -p $(dir $@) 2>/dev/null
	@echo -n $(dir $@) > $@
	@$(CC) -MM $< $(HDRS) >> $@

$(OBJS_DIR)%.db.d : $(SRCS_DIR)%.c
	@printf "   $(PURPLE)[INDEXING]$(RESET)\t$(notdir $@)\n"
	@-mkdir -p $(dir $@) 2>/dev/null
	@echo -n $(dir $@) > $@
	@$(CC) -MM $< $(HDRS) >> $@
	@sed -ri 's/(.*)\.o/\1.db.o/' $@

$(NAME) : $(OBJS_DEP) $(OBJS) $(STATIC_LIB)
	@$(CC) -o $(NAME) $(OBJS) $(STATIC_LIB) $(STATIC_LIB) $(LIB)
	@printf "   $(GREEN)[CREATING]$(RESET)\t$(CYAN)$(NAME)$(RESET)\n"

$(NAME_DB) : $(OBJS_DB_DEP) $(OBJS_DB) $(STATIC_LIB)
	@$(CC) -o $(NAME_DB) $(OBJS_DB) $(STATIC_LIB) $(STATIC_LIB) $(LIB)
	@printf "   $(GREEN)[CREATING]$(RESET)\t$(CYAN)$(NAME_DB)$(RESET)\n"

clean :
	@$(call submodules, clean)
	@printf "\n$(BLUE)$(BOLD)------- PROJECT DELETION ------$(RESET)\n"
	@if [ ! -d $(OBJS_DIR) ] ; then                                      \
	    printf " Nothing to $(RED)delete$(RESET)\n" ;                    \
	  else                                                               \
	    $(call the_clean, $(OBJS))                                       \
	    $(call the_clean, $(OBJS_DB))                                    \
	    $(call the_clean, $(OBJS_DEP))                                   \
	    $(call the_clean, $(OBJS_DIR))                                   \
	  fi ;
	@printf "\n"

fclean :
	@$(call submodules, fclean)
	@printf "\n$(BLUE)$(BOLD)------- PROJECT DELETION ------$(RESET)\n"
	@if [[ ! -d $(OBJS_DIR) && ! -f $(NAME) && ! -f $(NAME_DB) ]] ; then \
	    printf " Nothing to $(RED)delete$(RESET)\n" ;                    \
	  else                                                               \
	    $(call the_clean, $(OBJS))                                       \
	    $(call the_clean, $(OBJS_DB))                                    \
	    $(call the_clean, $(OBJS_DEP))                                   \
	    $(call the_clean, $(NAME_DB))                                    \
	    $(call the_clean, $(NAME))                                       \
	    $(call the_clean, $(OBJS_DIR))                                   \
	  fi ;
	@printf "\n"

re : fclean all

ifeq ($(MAKECMDGOALS), $(NAME))
  -include $(OBJS_DEP)
endif
