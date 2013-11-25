%Prolog

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Primeira parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Artigos pesoais
artigo(a).
artigo(o).

%adjetivos
adjetivo(professor).
adjetivo(professora).

%Verbos conjugados
verbo(da).

%Ponto
ponto('.').

%Banco de conhecimento
:- dynamic professor/1. %Por enquanto qualquer genero

:- dynamic disciplina/1.

:- dynamic da/2.

:- dynamic eh/2.

sentenca(X,[Ar,Ad,Pr,Vr,Di,Po],G) :- artigo(Ar),adjetivo(Ad),
                                     verbo(Vr),ponto(Po),
                                     asserta(professor(Pr)),
                                     asserta(disciplina(Di)),
                                     asserta(da(Pr,Di)).
                                     

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Segunda parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

downCaseList([],[]).
downCaseList([H|T], [Hl|Tl]) :- downcase_atom(H,Hl), downCaseList(T, Tl).

monta_lista(L) :- readln(X), downCaseList(X,L).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Terceira parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

