%Prolog

%Base do conhecimento
% TODO

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Primeira parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Artigos pesoais
artigo(a).
artigo(o).

%adjetivos
adjetivo(professor).
adjetivo(professora).

%Banco de conhecimento
:- dynamic da/2.
da(marcelo, mac239).

:- dynamic eh/2.
eh(mac425, [3, 5]).

%:- dynamic sentenca/3.
%sentenca(X,L,G) :- 




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Primeira parte %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fibonaci
:- dynamic fibo/2.
fibo(0, 1).
fibo(1, 1).
fibo(N, F) :- N >= 2, N1 is N - 1, N2 is N - 2,
              fibo(N1, F1), fibo(N2, F2), F is F1 + F2,
              asserta(fibo(N,F):-!). % adiciona no inicio
