if (d->stages[stage].rooms[id].name == 'R'){
                    //Créer une liste de monstre aléatoire, d'une taille aléatoire
                    int randomNumberMonster = 2 + rand() % (5 - 2);

                    //Liste de monstre de la room
                    d->stages[stage].rooms[id].newArrayMonster = malloc(sizeof(Monster) *randomNumberMonster +1);

                    for (int i = 0; i < randomNumberMonster; i++){
                        //pour chaque iteration, on crée un id randomMonsterId
                        int randomMonsterId = 0 + rand() % (9 - 0);
                        //pour chaque iteration randomMonsterId doit être différent de ceux déjà stocké dans le tableau
                        for (int j = 0; j < i; j++){
                            while (randomMonsterId == d->stages[stage].rooms[id].newArrayMonster[j].idMonster){
                                randomMonsterId = 0 + rand() % (9 - 0);
                            }
                        }
                        //ajout du monstre dans le tableau
                        Monster * monster = getMonsterById(arrayMonster,randomMonsterId);
                        d->stages[stage].rooms[id].newArrayMonster[i] = *monster;

                    }
                    //spawn des monstres du tableau newArrayMonster dans la room
                    // for(int y = 0; y < randomNumberMonster; y++ ){
                       // Monster * monsterDisplay = getMonsterById( d->stages[stage].rooms[id].newArrayMonster,0);
                      //  spawnMonster(d,monsterDisplay,stage,id);

                    // }
                // }
                     
                 
                }