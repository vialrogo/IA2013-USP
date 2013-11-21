%Prolog

%Base do conhecimento
homem(americo).
homem(daniel). 
homem(paulo). 
homem(carlos). 
homem(joaquim). 
homem(filipe). 
homem(jorge).
mulher(teresa). 
mulher(sonia). 
mulher(ana). 
mulher(carla). 
mulher(barbara). 
mulher(maria). 
mulher(thais).
idade(americo, 18). 
idade(daniel, 60). 
idade(paulo, 25). 
idade(carlos, 37). 
idade(joaquim, 80). 
idade(filipe, 32). 
idade(jorge, 104).
idade(teresa, 18). 
idade(sonia, 28). 
idade(ana, 17). 
idade(carla, 26). 
idade(barbara, 51). 
idade(maria, 79). 
idade(thais,103).
irmaos(americo, paulo).
irmaos(barbara,maria).
irmaos(carlos, sonia). 
pai(carlos, teresa). 
pai(daniel, americo). 
pai(daniel, paulo). 
pai(joaquim, daniel).
pai(jorge,joaquim). 
mae(maria, daniel). 
mae(barbara, ana). 
casados(filipe, carla). 
casados(americo,teresa). 
casados(joaquim, maria).
casados(jorge,thais).

% (a) avof(Mul, Pess) em que Mul seja avó de Pess.
avof(Mul,Pess) :- mae(Mul,X), pai(X,Pess).
avof(Mul,Pess) :- mae(Mul,X), mae(X,Pess).

% (b) avom(Hom, Pess) em que Hom seja avô de Pess.
avom(Hom,Pess) :- pai(Hom,X), pai(X,Pess).
avom(Hom,Pess) :- pai(Hom,X), mae(X,Pess).

% (c) bisavom(Hom, Pess) que sucede se Hom for bisavô de Pess.
bisavom(Hom,Pess) :- pai(Hom,X), avom(X,Pess).
bisavom(Hom,Pess) :- pai(Hom,X), avof(X,Pess).

% (d) primo_1(P1, P2) que sucede se P1 e P2 forem primos em primeiro grau.
pai_ou_mae(PaiMae, Filho) :- pai(PaiMae, Filho).
pai_ou_mae(PaiMae, Filho) :- mae(PaiMae, Filho).

primo_1(P1,P2) :- pai_ou_mae(X,P1), pai_ou_mae(Y,P2), irmaos(X,Y).
primo_1(P1,P2) :- pai_ou_mae(X,P1), pai_ou_mae(Y,P2), irmaos(Y,X).

% (e) primo(P1, P2) que sucede se P1 e P2 forem primos em qualquer grau.
primo(P1,P2) :- primo_1(P1,P2).
primo(P1,P2) :- pai_ou_mae(X,P2), primo(X,P1).
primo(P1,P2) :- pai_ou_mae(X,P1), primo(X,P2).

% (f) maior_de_idade(Pess) que sucede se Pess for maior de idade.
maior_de_idade(Pess) :- idade(Pess, X), X>17.

% (g) pessoas(Lista) que devolve a Lista de todas as pessoas existentes na base de conhecimento.
pessoa(Pess) :- homem(Pess).
pessoa(Pess) :- mulher(Pess).

pessoas(Lista) :- findall(X, pessoa(X), Lista).

% (h) mais_velho(Pess) que retorna a pessoa mais velha que consta na base de conhecimento.
mais_velho(Pess) :- findall(X,idade(_,X),Lista), max_list(Lista, X), idade(Pess,X).

% (i) lista_pessoas(Lista,Sexo) que retorne uma lista de todas as pessoas do Sexo indicado (m/f), incluindo as suas respectivas idades. Por exemplo lista_pessoas(Lista, m) deveria retornar Lista=[americo-18,daniel-60,paulo-25,carlos-37,joaquim-80,filipe-32].
lista_homens(X,Y)   :- homem(X),  idade(X,Y).
lista_mulheres(X,Y) :- mulher(X), idade(X,Y).

lista_pessoas(Lista,m) :- findall(X-Y, lista_homens(X,Y),   Lista).
lista_pessoas(Lista,f) :- findall(X-Y, lista_mulheres(X,Y), Lista).

% (j) adequados(Hom, Mul) que sucede se Hom for um homem, Mul for uma mulher e o homem for (no máximo) 2 anos mais novo do que a mulher ou 10 anos mais velho do que ela e se ambos não tiverem nenhuma relação de parentesco nem nenhum deles for casado.
idade_adequada(Hom, Mul) :- idade(Hom,X), idade(Mul,Y), X >= Y-2, X < Y+11.

ancestral(P1,P1).
ancestral(P1,P2) :- pai_ou_mae(P1,X), ancestral(X,P2).

parentesco(P1,P2) :- ancestral(P1,P2).
parentesco(P1,P2) :- ancestral(P2,P1).
parentesco(P1,P2) :- primo(P1,P2).

casado(Pess) :- casados(Pess,_).
casado(Pess) :- casados(_,Pess).

adequados(Hom, Mul) :- homem(Hom), mulher(Mul), idade_adequada(Hom,Mul),
                       not(parentesco(Hom,Mul)), not(casado(Hom)), not(casado(Mul)).

