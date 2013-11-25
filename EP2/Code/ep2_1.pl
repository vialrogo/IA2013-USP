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
verbo(eh).

%Ponto
ponto('.').

%Pergunta
pergunta(?).

%Banco de conhecimento
:- dynamic professor/1.
:- dynamic professora/1.
:- dynamic disciplina/1.
:- dynamic da/2.
:- dynamic eh/2.

%Inserções
inserir(X,[Ar,Ad,Pr,Vr,Di]) :- artigo(Ar),adjetivo(Ad),verbo(Vr),
                                  P =.. [Ad,Pr], assertz(P),
                                  assertz(disciplina(Di)),
                                  X =.. [Vr, Pr, Di], assertz(X).

%Sentenca
sentenca(X,Frase,G) :- reverse(Frase,[H|T]),ponto(H),reverse(T,F),inserir(X,F). 
sentenca(X,Frase,G) :- reverse(Frase,[H|T]),pergunta(H),reverse(T,F),responder(X,F). 

%Apagar tudo
apagar :-   retractall(professor(_)),
            retractall(professora(_)),
            retractall(disciplina(_)),
            retractall(da(_,_)),
            retractall(eh(_,_)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Segunda parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

downCaseList([],[]).
downCaseList([H|T], [Hl|Tl]) :- downcase_atom(H,Hl), downCaseList(T, Tl).

monta_lista(L) :- readln(X), downCaseList(X,L).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Terceira parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

