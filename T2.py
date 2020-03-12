from threading import Thread
import sys
import time


class Relatorios:
    def __init__(self, nomePaciente, nomeMedico, codSequencial, dataInternacao,
                 codMotivoInternacao, listaSintoma, tamanho):
        self.nomePaciente = nomePaciente
        self.nomeMedico = nomeMedico
        self.codSequencial = codSequencial
        self.dataInternacao = dataInternacao
        self.codMotivoInternacao = codMotivoInternacao
        self.listaSintoma = listaSintoma
        self.tamanho = tamanho

    def __str__(self):
        return (self.nomePaciente + "," + self.nomeMedico + "," +
                self.codSequencial + "," + self.dataInternacao + "," +
                self.codMotivoInternacao + "," + self.listaSintoma + "," +
                self.tamanho)


def criaPilha(ini, fim, relatorios):
    a = []
    for i in range(ini, fim + 1):
        a.append(relatorios[i])
    return a


def ordernar(opcao, index):
    if (opcao == '1'):
        pilhas[index].sort(key=lambda x: x.nomePaciente, reverse=True)
    elif (opcao == '2'):
        pilhas[index].sort(key=lambda x: x.nomeMedico, reverse=True)
    elif (opcao == '3'):
        pilhas[index].sort(key=lambda x: (x.nomePaciente, x.nomeMedico),
                           reverse=True)


def comparaNomePaciente():
    maior = max
    index = 0
    for i in range(len(pilhas)):
        if (len(pilhas[i]) > 0 and pilhas[i][-1].nomePaciente < maior):
            maior = pilhas[i][-1].nomePaciente
            index = i
    return index


def comparaNomeMedico():
    maior = max
    index = 0
    for i in range(len(pilhas)):
        if (len(pilhas[i]) == 0):
            pass
        elif (pilhas[i][-1].nomeMedico < maior):
            maior = pilhas[i][-1].nomeMedico
            index = i
    return index


def vencedorNomePaciente(result):
    indexVencedor = 0
    while (len(pilhas[0]) != 0 or len(pilhas[1]) != 0 or len(pilhas[2]) != 0
           or len(pilhas[3]) != 0 or len(pilhas[4]) != 0 or len(pilhas[5]) != 0
           or len(pilhas[6]) != 0 or len(pilhas[7]) != 0):
        indexVencedor = comparaNomePaciente()
        result.append(pilhas[indexVencedor].pop())


def vencedorNomeMedico(result):
    indexVencedor = 0
    while (len(pilhas[0]) != 0 or len(pilhas[1]) != 0 or len(pilhas[2]) != 0
           or len(pilhas[3]) != 0 or len(pilhas[4]) != 0 or len(pilhas[5]) != 0
           or len(pilhas[6]) != 0 or len(pilhas[7]) != 0):
        indexVencedor = comparaNomeMedico()
        result.append(pilhas[indexVencedor].pop())


def escreveArquivo(result):
    file = open(r"ordenado.csv", "w")
    file.write(
        "Nome do Paciente,Nome do Medico,Codigo Sequencial,Data Internacao,Codigo Motivo Internacao,Lista de Sintomas,Tamanho em Bytes, Index\n"
    )
    for i in range(len(result)):
        file.write("{},{}\n".format(result[i], i))


start = time.time()
print("Lendo os relatorios...\n")

with open("relatorios.csv", "r") as f:
    data = f.readlines()

relatorios = []
valores = []
aux = ""
count = 0
size = 0
max = "ZZZZZZZZZ"

for i in range(1, len(data), 1):
    for letter in data[i]:
        if (letter == ',' and count < 5):
            valores.append(aux)
            aux = ""
            count = count + 1
        elif (letter == ','):
            pass
        elif (letter == '\n' and aux != ""):
            size = sys.getsizeof(valores[0]) + sys.getsizeof(
                valores[1]) + sys.getsizeof(valores[2]) + sys.getsizeof(
                    valores[3]) + sys.getsizeof(aux)
            a = Relatorios(valores[0], valores[1], valores[2], valores[3],
                           valores[4], aux, str(size))
            relatorios.append(a)
            del a
            aux = ""
            valores[:] = []
            count = 0
            size = 0
        elif (letter == "\n"):
            size = sys.getsizeof(valores[0]) + sys.getsizeof(
                valores[1]) + sys.getsizeof(valores[2]) + sys.getsizeof(
                    valores[3]) + sys.getsizeof(aux)
            a = Relatorios(valores[0], valores[1], valores[2], valores[3],
                           valores[4], aux, str(size))
            relatorios.append(a)
            del a
            valores[:] = []
            count = 0
            size = 0
        else:
            aux = aux + letter

end = time.time()

print("Relatorios lido em {}s\n".format(end - start))

# Criacao das 8 pilhas
tamanho = int(len(relatorios) / 8)

ini = 0
fim = tamanho - 1
pilhas = []

start = time.time()
print("Criando as pilhas... \n")

for i in range(7):
    pilhas.append(criaPilha(ini, fim, relatorios))
    ini = fim + 1
    fim = ini + tamanho - 1

pilhas.append(criaPilha(ini, len(relatorios) - 1, relatorios))

end = time.time()

print("Pilhas criadas em {}s\n".format(end - start))

opcao = input(
    "Digite 1 para order por nomePaciente\nDigite 2 para ordernar por nomeMedico\nDigite 3 para ordernar por nomePaciente e nomeMedico\n"
)

if (int(opcao) > 3 or int(opcao) < 1):
    print("Opcao invalida!!\n")
    sys.exit()

threads = [None] * 8

try:
    start = time.time()
    print("Ordenando as pilhas por threads... \n")
    for i in range(len(pilhas)):
        threads[i] = Thread(target=ordernar, args=(opcao, i))
        threads[i].start()
except:
    print("Erro ao inicializar as threads")

for t in threads:
    t.join()

end = time.time()

print("Pilhas ordenadas em {}s\n".format(end - start))

result = []
indexVencedor = 0

start = time.time()
print("Comparando o topo das pilhas... \n")

if (opcao == '1' or opcao == '3'):
    vencedorNomePaciente(result)
elif (opcao == '2'):
    vencedorNomeMedico(result)

end = time.time()

print("Pilhas esvaziadas em {}s\n".format(end - start))

start = time.time()
print("Escrevendo o resultado no arquivo... \n")

escreveArquivo(result)

end = time.time()

print("Arquivo escrito em {}s\n".format(end - start))
