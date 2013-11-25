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

%Pontuação
ponto('.').
pergunta(?).

%conjunção
conjuncao(e).

%Adverbio
adverbio(aas).

%Dias
dia(segundas).
dia(tercas).
dia(quartas).
dia(quintas).
dia(sextas).
dia(sabados).
dia(domingos).

%Predicado que confirma se alguma coisa é uma lista de dias com conjunções
lista_dias([]).
lista_dias([H | [] ]) :- dia(H), !.
lista_dias([D,C|R])   :- dia(D), conjuncao(C), lista_dias(R).

%Converte um dia num número
convertDia(segundas, 2).
convertDia(tercas, 3). 
convertDia(quartas, 4).
convertDia(quintas, 5).
convertDia(sextas, 6).
convertDia(sabados, 7).
convertDia(domingos, 1).

%Converte uma lista de dias, numa lista de números e apaga as conuunções
convertLD([],[]).
convertLD([H | []], [Hc | []]) :- convertDia(H, Hc), !.
convertLD( [H, _ |T], [Hc|Tc]) :- convertDia(H, Hc), convertLD(T, Tc).

%Banco de conhecimento
:- dynamic professor/1.
:- dynamic professora/1.
:- dynamic disciplina/1.
:- dynamic da/2.
:- dynamic eh/2.

%Inserções
inserir(X,[Ar,Ad,Pr,Vr,Di]) :-  artigo(Ar),adjetivo(Ad),verbo(Vr),
                                P =.. [Ad,Pr], assertz(P),
                                assertz(disciplina(Di)),
                                X =.. [Vr, Pr, Di], assertz(X).

inserir(X,[Di,Vr,Adv|Ld]) :- verbo(Vr),adverbio(Adv),lista_dias(Ld),
                             assertz(disciplina(Di)),
                             convertLD(Ld,Ldn),
                             X =.. [Vr, Di, Ldn], assertz(X).

%Sentenca
sentenca(X,Frase,_) :-  reverse(Frase,[H|T]),ponto(H),reverse(T,F),
                        inserir(X,F), !. 
sentenca(X,Frase,_) :-  reverse(Frase,[H|T]),pergunta(H),reverse(T,F),
                        responder(X,F), !. 

%Apagar tudo
apagar :-   retractall(professor(_)),
            retractall(professora(_)),
            retractall(disciplina(_)),
            retractall(da(_,_)),
            retractall(eh(_,_)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Segunda parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Downcase duma lista
downCaseList([],[]).
downCaseList([H|T], [Hl|Tl]) :- downcase_atom(H,Hl), downCaseList(T, Tl).

%Monta lista
monta_lista(L) :- readln(X), downCaseList(X,L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Terceira parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

