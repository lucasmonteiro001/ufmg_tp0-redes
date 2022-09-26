# tp0_redes

git clone // faz o clone do reposito do github para a sua maquina // nao esquece de criar um projeto no eclipse e fazer o clone dentro da pasta src/

git status // checa o estado dos arquivos localmente, quais faltam comitar git log // checa o historico de commits local git add * // adiciona os arquivos alterados git commit - m "mensagem" // commita e salva no repositorio local git push // pega o commit e envia para o github

git pull // faz o download das atualizacoes que estao no github

#### BOAS PRATICAS

Sempre que for alterar o arquivo, faz o download mais atual do respositorio
Sempre que terminar de fazer alguma alterar importante, sobre o codigo pro github
##### DÚVIDAS NO CÓDIGO

Lucas não entendi o cod: 0x1 no mensagem.c, não seria um código para cada operação? Resposta: Entao, pelo que entendi, aquilo eh o codigo da msg, 0x1 para desafio e 0x2 para resposta. Tenho que confirmar com o professor, mas de qualquer forma to passando eles na msg.
Gostaria que me explicasse essa parte : " struct timeval t1; gettimeofday(&t1, NULL); srand(t1.tv_usec * t1.tv_sec);" implementados no operação.c para escolher randômicamente operadores.c em randNumero erandOperador. Resposta: N'ao tenho mto que explicar nao haha. Na vdd, tava procurando uma funcao para gerar valores randomicos, e essa foi a melhor que encontrei. Nao tirei ela da minha cabeca nao, na vdd nunca tinha ouvido falar. Mas sei que ela gera valores baseada no tempo.
Qual é o mínimo e máximo dos operandos dos desafios? 0 a 100? Devemos gerar qualquer número inteiro não negativo para as operações. Resposta: Acho que eh isso msm, acho que temos que gerar de 0 - 99, vou consertar isso depois.
Na sua operação calcula apenas no caso de exponeciação você tratou no caso da resposta ser negativa; adicionei tbm na parte de subtração. Resposta: Valeu
Deletei aquele hello.c Resposta: Blz
