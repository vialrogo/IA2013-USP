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
spergunta(?).

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

%Converte uma lista de dias numa lista de números e apaga as conjunções
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

inserir(X,[Ar,Ad,Pr,Vr,Di,Adv|Ld]) :- artigo(Ar),adjetivo(Ad),verbo(Vr),
                                      adverbio(Adv),lista_dias(Ld),
                                      inserir(X,[Ar,Ad,Pr,Vr,Di]).

inserir(X,[Ar,Ad,_,Vr,Di,Adv|Ld]) :- artigo(Ar),adjetivo(Ad),verbo(Vr),
                                     adverbio(Adv),lista_dias(Ld),
                                     inserir(X,[Di,eh,Adv|Ld]).

%Sentenca
sentenca(X,Frase,_) :-  reverse(Frase,[H|T]),ponto(H),reverse(T,F),inserir(X,F). 
sentenca(_,Frase,_) :-  reverse(Frase,[H|T]),spergunta(H),reverse(T,F),responder(F). 

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

%Perguntas
pergunta(quem).
pergunta(quando).

oque([o, que]).

%Monta uma lista com um elemento repetido, a quantidade de elementos de outra
%lista. Serve para writes repetidos
montarListaS(_,[],[]).  
montarListaS(S,[_|T],X) :- montarListaS(S,T,Y), append([S],Y,X).

% Consulta: "Quem da macxxx?"
% Resposta: "O professor yyy da macxxx."
responder([quem, da | X]) :- disciplina(X)) -> Di is X; (oque(X) -> true; false)), 
                             findall([Pr,Di], da(Pr,Di), L),
                             montarListaS('O professor %w da %w\n',L,S),
                             maplist(writef,S,L).

% Consulta: "Quem da o que?"
% Resposta: "O profesor yy1 da macxx1.
% A professora yy2 da mac xx2.
% ...."
responder([quem, da, o, que]) :- findall([Pr,Di], da(Pr,Di), L),
                                 montarListaS('O professor %w da %w\n',L,S),
                                 maplist(writef,S,L).

% Consulta: "Quando eh macxxx?"
% Resposta: "Macxxx eh as yyy e zzz."
responder([quando, eh, o, que]) :- findall([Di,Ho], eh(Di,Ho), L),
                                 montarListaS('%w eh aas %w\n',L,S),
                                 maplist(writef,S,L).

% Consulta: "O que o professor xxx da?"
% Resposta: "O professor xxx da macyyy."

% Consulta: "O que a professora xxx da?"
% Resposta: "A professora xxx da macyyy."

%Conlusta ao programa
consulta :- monta_lista(L), sentenca(_,L,_).

