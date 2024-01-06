using CsvHelper;
using CsvHelper.Configuration;
using System;
using System.Collections.Generic;
using System.Formats.Asn1;
using System.Globalization;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Resources;
using static GestaoAlojamentoTuristico.Reserva;



namespace GestaoAlojamentoTuristico
{
    /// <summary>
    /// Classe para armazenar todas as funções de utilidades do programa.
    /// </summary>
    public class Utility
    {
        #region MANIPULAÇÃO DE ARQUIVOS

        private const string ArquivoHoteis = @"..\..\..\Arquivos\Hoteis.csv";
        private const string ArquivoHospedes = @"..\..\..\Arquivos\Hospedes.csv";
        private const string ArquivoQuartos = @"..\..\..\Arquivos\Quartos.csv";
        private const string ArquivoReservas = @"..\..\..\Arquivos\Reservas.csv";

        public static DateTime dataAtual = DateTime.Now;

        /// <summary>
        /// Método para criar um arquivo caso não exista.
        /// </summary>
        /// <param name="caminho">O caminho do arquivo.</param>
        /// <returns></returns>
        static bool CriarArquivo(string caminho)
        {
            try
            {
                using (StreamWriter writer = File.CreateText(caminho))
                    return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        /// <summary>
        /// Método que carrega os dados de hotéis salvos em arquivo.
        /// </summary>
        public static void CarregarHoteisEmArquivo()
        {
            if (File.Exists(ArquivoHoteis))
            {
                Hotel.ListaHoteis.Clear();

                using (StreamReader reader = new StreamReader(ArquivoHoteis))
                {
                    string linha;
                    while ((linha = reader.ReadLine()) != null)
                    {
                        string[] dados = linha.Split(',');
                        if (dados.Length == 6)
                        {
                            int id = int.Parse(dados[0]);
                            int REF = int.Parse(dados[1]);
                            string username = dados[2];
                            string password = dados[3];
                            string nome = dados[4];
                            string tipo = dados[5];
                            Hotel.ListaHoteis.Add(new Hotel(REF, username, password, nome, tipo));
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Método que carrega os dados de hospedes salvos em arquivo.
        /// </summary>
        public static void CarregarHospedesEmArquivo()
        {
            if (File.Exists(ArquivoHospedes))
            {
                Hospede.ListaHospedes.Clear();

                using (StreamReader reader = new StreamReader(ArquivoHospedes))
                {
                    string linha;
                    while ((linha = reader.ReadLine()) != null)
                    {
                        string[] dados = linha.Split(',');
                        if (dados.Length == 6)
                        {
                            int id = int.Parse(dados[0]);
                            int nif = int.Parse(dados[1]);
                            string username = dados[2];
                            string password = dados[3];
                            string nome = dados[4];
                            string tipo = dados[5];
                            Hospede.ListaHospedes.Add(new Hospede(nif, username, password, nome, tipo));
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Método que carrega os dados de quartos salvos em arquivo.
        /// </summary>
        public static void CarregarQuartosEmArquivo()
        {
            if (File.Exists(ArquivoQuartos))
            {
                Quarto.ListaQuartos.Clear();

                using (StreamReader reader = new StreamReader(ArquivoQuartos))
                {
                    string linha;
                    while ((linha = reader.ReadLine()) != null)
                    {
                        string[] dados = linha.Split(',');
                        if (dados.Length == 8)
                        {
                            int hotelid;
                            if (int.TryParse(dados[0], out hotelid))
                            {
                                Hotel hotelREF = Hotel.EncontrarHotelRef(hotelid);

                                int quartoid;
                                if (int.TryParse(dados[1], out quartoid))
                                {
                                    int numeroquarto;
                                    if (int.TryParse(dados[2], out numeroquarto))
                                    {
                                        string tipo = dados[3];
                                        string descricaoquarto = dados[4];
                                        int andar;
                                        if (int.TryParse(dados[5], out andar))
                                        {
                                            int capacidade;
                                            if (int.TryParse(dados[6], out capacidade))
                                            {
                                                decimal diaria;
                                                if (decimal.TryParse(dados[7], out diaria))
                                                {
                                                    Quarto.ListaQuartos.Add(new Quarto(hotelREF, numeroquarto, tipo, descricaoquarto, andar, capacidade, diaria));
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Erro 1");
                                                }
                                            }
                                            else
                                            {
                                                Console.WriteLine("Erro 2");
                                            }
                                        }
                                        else
                                        {
                                            Console.WriteLine("Erro 3");
                                        }
                                    }
                                    else
                                    {
                                        Console.WriteLine("Erro 4");
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("Erro 5");
                                }
                            }
                            else
                            {
                                Console.WriteLine("Erro 6");
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Método que carrega os dados de reservas salvas em arquivo.
        /// </summary>
        public static void CarregarReservasEmArquivo()
        {
            if (File.Exists(ArquivoReservas))
            {
                string[] linhas = File.ReadAllLines(ArquivoReservas);

                if (linhas.Length > 0)
                {
                    for (int i = 0; i < linhas.Length; i++)
                    {
                        string[] colunas = linhas[i].Split(',');

                        if (colunas.Length >= 9)
                        {
                            int quartoId = int.Parse(colunas[1]);
                            DateTime dataInicio = DateTime.ParseExact(colunas[2], "dd/MM/yyyy HH:mm:ss", CultureInfo.InvariantCulture);
                            DateTime dataFim = DateTime.ParseExact(colunas[3], "dd/MM/yyyy HH:mm:ss", CultureInfo.InvariantCulture);
                            decimal precoTotal = decimal.Parse(colunas[4]);
                            StatusReserva status = (StatusReserva)Enum.Parse(typeof(StatusReserva), colunas[5]);
                            DateTime dataCheckIn = DateTime.ParseExact(colunas[6], "dd/MM/yyyy HH:mm:ss", CultureInfo.InvariantCulture);
                            DateTime dataCheckOut = DateTime.ParseExact(colunas[7], "dd/MM/yyyy HH:mm:ss", CultureInfo.InvariantCulture);
                            int hospedeId = int.Parse(colunas[8]);
                            int hotelId = int.Parse(colunas[9]);

                            Hospede hospede = Hospede.EncontrarHospedeId(hospedeId);
                            Hotel hotel = Hotel.EncontrarHotelRef(hotelId);
                            Quarto quarto = GestaoQuarto.EncontrarQuartoNumero(quartoId);

                            Reserva.ListaReservas.Add(new Reserva(dataInicio, dataFim, dataCheckIn, dataCheckOut, precoTotal, status, hospede, hotel, quarto));
                        }
                        else
                        {
                        }
                    }
                }
                else
                {
                }
            }
            else
            {
            }
        }

        /// <summary>
        /// Método que salva os dados de hoteis em arquivo.
        /// </summary>
        public static void SalvarHotelEmArquivo()
        {
            if (!File.Exists(ArquivoHoteis))
            {
                CriarArquivo(ArquivoHoteis);
            }

            List<string> linhasExistentes = File.ReadAllLines(ArquivoHoteis).ToList();
            using (StreamWriter writer = new StreamWriter(ArquivoHoteis, true))
            {
                foreach (var hotel in Hotel.ListaHoteis)
                {
                    string linha = $"{hotel.IdUtilizador},{hotel.HotelREF},{hotel.UsernameUtilizador},{hotel.PasswordUtilizador},{hotel.NameUtilizador},{hotel.TypeUtilizador}";

                    if (!linhasExistentes.Contains(linha))
                    {
                        writer.WriteLine(linha);
                        linhasExistentes.Add(linha);
                    }
                }
            }
        }

        /// <summary>
        /// Método que salva os dados de hospedes em arquivo.
        /// </summary>
        public static void SalvarHospedesEmArquivo()
        {
            if (!File.Exists(ArquivoHospedes))
            {
                CriarArquivo(ArquivoHospedes);
            }
            List<string> linhasExistentes = File.ReadAllLines(ArquivoHospedes).ToList();

            using (StreamWriter writer = new StreamWriter(ArquivoHospedes, true))
            {
                foreach (var hospede in Hospede.ListaHospedes)
                {
                    string linha = $"{hospede.IdUtilizador},{hospede.HospedeNIF},{hospede.UsernameUtilizador},{hospede.PasswordUtilizador},{hospede.NameUtilizador},{hospede.TypeUtilizador}";

                    if (!linhasExistentes.Contains(linha))
                    {
                        writer.WriteLine(linha);
                        linhasExistentes.Add(linha);
                    }
                }
            }
        }

        /// <summary>
        /// Método que salva os dados de quartos em arquivo.
        /// </summary>
        public static void SalvarQuartosEmArquivo()
        {
            if (!File.Exists(ArquivoQuartos))
            {
                CriarArquivo(ArquivoQuartos);
            }
            List<string> linhasExistentes = File.ReadAllLines(ArquivoQuartos).ToList();

            using (StreamWriter writer = new StreamWriter(ArquivoQuartos, true))
            {
                foreach (var quartos in Quarto.ListaQuartos)
                {
                    string linha = $"{quartos.Hotel.HotelREF},{quartos.QuartoId},{quartos.QuartoNumero},{quartos.QuartoTipo},{quartos.QuartoDescricao},{quartos.QuartoAndar},{quartos.QuartoCapacidade},{quartos.QuartoDiaria}";

                    if (!linhasExistentes.Contains(linha))
                    {
                        writer.WriteLine(linha);
                        linhasExistentes.Add(linha);
                    }
                }
            }
        }

        /// <summary>
        /// Método que salva os dados de reservas em arquivo.
        /// </summary>
        public static void SalvarReservasEmArquivo()
        {
            if (!File.Exists(ArquivoReservas))
            {
                CriarArquivo(ArquivoReservas);
            }

            List<string> linhasExistentes = File.ReadAllLines(ArquivoReservas).ToList();

            for (int i = 0; i < ListaReservas.Count; i++)
            {
                var reservas = ListaReservas[i];
                string linha = $"{reservas.ReservaId},{reservas.QuartoAtual.QuartoNumero},{reservas.ReservaInicio},{reservas.ReservaFim},{reservas.TotalCost},{reservas.EstadoReserva},{reservas.InCheck},{reservas.OutCheck},{reservas.HospedeAtual.HospedeNIF},{reservas.HotelAtual.HotelREF}";

                int indiceExistente = -1;

                for (int j = 0; j < linhasExistentes.Count; j++)
                {
                    if (linhasExistentes[j].StartsWith($"{reservas.ReservaId},"))
                    {
                        indiceExistente = j;
                        break;
                    }
                }

                if (indiceExistente != -1)
                {
                    linhasExistentes[indiceExistente] = linha;
                }
                else
                {
                    linhasExistentes.Add(linha);
                }
            }

            File.WriteAllLines(ArquivoReservas, linhasExistentes);
        }
        #endregion

        /// <summary>
        /// A classe fornece métodos auxiliares para acessar recursos, como mensagens localizadas.
        /// </summary>
        public static class ResourceHelper
        {
            private static readonly ResourceManager ResourceManager = new ResourceManager("GestaoAlojamentoTuristico.Resources.Messages", typeof(ResourceHelper).Assembly);

            /// <summary>
            /// Método que obtém uma string localizada correspondente à chave especificada e à cultura fornecida.
            /// </summary>
            /// <param name="key"></param>
            /// <param name="culture"></param>
            /// <param name="args"></param>
            /// <returns></returns>
            public static string GetString(string key, string culture, params object[] args)
            {
                CultureInfo currentCulture = new CultureInfo(culture);
                return ResourceManager.GetString(key, currentCulture);
            }
        }
    }
}