worldCupDB: wc.o wt.o wp.o
	gcc wc.o wt.o wp.o -o worldCupDB
	@rm -f *.o
	@echo "Job completed"
wc.o: worldCupDB.c worldCupDB.h
	gcc -c worldCupDB.c -o wc.o
wt.o: worldcup_team.c worldcup_team.h
	gcc -c worldcup_team.c -o wt.o
wp.o: worldcup_player.c worldcup_player.h
	gcc -c worldcup_player.c -o wp.o
clean:
	@rm -f *.o worldCupDB
	@echo "Clean done"
