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

namespace GestaoAlojamentoTuristico
{
    /// <summary>
    /// Classe que representa os quarto no sistema de gerenciamento de alojamentos turisticos.
    /// </summary>
    internal class Quarto
    {
        public static List<Quarto> ListaQuartos = new List<Quarto>();

        #region ATRIBUTOS
        private int IdQuarto;
        private static int proximoquartoid = 1;
        private int NumeroQuarto;
        private string TipoQuarto;
        private string DescricaoQuarto;
        private TimeSpan Reservado_em;
        private int AndarQuarto;
        private int CapacidadeQuarto;
        private decimal DiariaQuarto;
        private Hospede? HospedeAtual;
        private Hotel? HotelAtual;
        #endregion

        #region PROPRIEDADES
        public int QuartoId
        {
            get { return IdQuarto; }
            set { IdQuarto = value; }
        }

        public int QuartoNumero
        {
            get { return NumeroQuarto; }
            set { NumeroQuarto = value; }
        }

        public string QuartoTipo
        {
            get { return TipoQuarto; }
            set { TipoQuarto = value; }
        }

        public string QuartoDescricao
        {
            get { return DescricaoQuarto; }
            set { DescricaoQuarto = value; }
        }

        public int QuartoAndar
        {
            get { return AndarQuarto; }
            set { AndarQuarto = value; }
        }

        public int QuartoCapacidade
        {
            get { return CapacidadeQuarto; }
            set { CapacidadeQuarto = value; }
        }

        public decimal QuartoDiaria
        {
            get { return DiariaQuarto; }
            set { DiariaQuarto = value; }
        }

        public Hotel Hotel { get; set; }

        public List<Reserva> Reservas = Reserva.ListaReservas;

        #endregion

        #region CONSTRUTORES        
        /// <summary>
        /// Inicializa uma nova instancia da classe Quarto com valores padrões. <see cref="Quarto"/>.
        /// </summary>
        public Quarto()
        {
            IdQuarto = 1;
            NumeroQuarto = 0;
            TipoQuarto = "";
            DescricaoQuarto = "";
            AndarQuarto = 0;
            CapacidadeQuarto = 0;
            DiariaQuarto = 0;
            HospedeAtual = null;
            HotelAtual = null;
        }

        /// <summary>
        /// Inicializa uma nova instancia da classe Quarto com parametros especificos. <see cref="Quarto"/>.
        /// </summary>
        /// <param name="numeroquarto">The numeroquarto.</param>
        /// <param name="tipoquarto">The tipoquarto.</param>
        /// <param name="descricaoquarto">The descricaoquarto.</param>
        /// <param name="andar">The andar.</param>
        /// <param name="capacidade">The capacidade.</param>
        /// <param name="diaria">The diaria.</param>
        public Quarto(Hotel hotel, int numeroquarto, string tipoquarto, string descricaoquarto, int andar, int capacidade, decimal diaria)
        {
            Hotel = hotel;
            QuartoId = proximoquartoid++;
            NumeroQuarto = numeroquarto;
            TipoQuarto = tipoquarto;
            DescricaoQuarto = descricaoquarto;
            AndarQuarto = andar;
            CapacidadeQuarto = capacidade;
            DiariaQuarto = diaria;
        }
        #endregion

        #region MÉTODOS        

        /// <summary>
        /// Método que realiza a verificação da disponibilidade do quarto na data informada. 
        /// </summary>
        /// <param name="dataInicio">A data de inicio.</param>
        /// <param name="dataFim">A data de fim.</param>
        /// <returns></returns>
        public bool EstaDisponivel(DateTime dataInicio, DateTime dataFim)
        {
            foreach (var reserva in Reserva.ListaReservas)
            {
                if (this == reserva.QuartoAtual)
                {
                    if (dataInicio >= reserva.ReservaInicio && dataInicio <= reserva.ReservaFim ||
                        dataFim >= reserva.ReservaInicio && dataFim <= reserva.ReservaFim ||
                        dataInicio <= reserva.ReservaInicio && dataFim >= reserva.ReservaFim)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        #endregion
    }

    /// <summary>
    /// Classe que representa a gestão de quartos no sistema de gerenciamento de alojamentos turisticos
    /// </summary>
    public class GestaoQuarto
    {
        List<Reserva> listareservas = Reserva.ListaReservas;

        #region MÉTODOS

        /// <summary>
        /// Método para criar um quarto.
        /// </summary>
        public static void CriaQuarto()
        {
            Console.WriteLine(Utility.ResourceHelper.GetString("RefHotel", Program.CurrentCulture));
            int REF = int.Parse(Console.ReadLine().Trim());

            Hotel HotelSelecionado = Hotel.EncontrarHotelRef(REF);

            Console.WriteLine(Utility.ResourceHelper.GetString("NumberRoom", Program.CurrentCulture));
            int numeroquarto = int.Parse(Console.ReadLine().Trim());

            Console.WriteLine(Utility.ResourceHelper.GetString("TypeRoom", Program.CurrentCulture));
            string tipoquarto = Console.ReadLine().Trim();

            Console.WriteLine(Utility.ResourceHelper.GetString("DescRoom", Program.CurrentCulture));
            string descquarto = Console.ReadLine().Trim();

            Console.WriteLine(Utility.ResourceHelper.GetString("FloorRoom", Program.CurrentCulture));
            int andar = int.Parse(Console.ReadLine().Trim());

            Console.WriteLine(Utility.ResourceHelper.GetString("CapacityRoom", Program.CurrentCulture));
            int capacidade = int.Parse(Console.ReadLine().Trim());

            Console.WriteLine(Utility.ResourceHelper.GetString("PerNight", Program.CurrentCulture));
            decimal diaria = decimal.Parse(Console.ReadLine().Trim());

            Quarto.ListaQuartos.Add(new Quarto(HotelSelecionado, numeroquarto, tipoquarto, descquarto, andar, capacidade, diaria));
            Utility.SalvarQuartosEmArquivo();
            Console.Clear();
        }

        /// <summary>
        /// Método para editar um quarto pelo numero de quarto.
        /// </summary>
        public static void EditaQuarto()
        {
            Console.WriteLine(Utility.ResourceHelper.GetString("NumberRoom", Program.CurrentCulture));
            int NumeroQuartoEdit = int.Parse(Console.ReadLine().Trim());

            Quarto QuartoEdit = Quarto.ListaQuartos.Find(u => u.QuartoNumero == NumeroQuartoEdit);

            if (QuartoEdit != null)
            {
                Console.WriteLine(Utility.ResourceHelper.GetString("TypeRoom", Program.CurrentCulture));
                QuartoEdit.QuartoTipo = Console.ReadLine().Trim();
                Console.WriteLine(Utility.ResourceHelper.GetString("DescRoom", Program.CurrentCulture));
                QuartoEdit.QuartoDescricao = Console.ReadLine().Trim();
                Console.WriteLine(Utility.ResourceHelper.GetString("CapacityRoom", Program.CurrentCulture));
                QuartoEdit.QuartoCapacidade = int.Parse(Console.ReadLine().Trim());
                Console.WriteLine(Utility.ResourceHelper.GetString("PerNight", Program.CurrentCulture));
                QuartoEdit.QuartoDiaria = int.Parse(Console.ReadLine().Trim());

                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("QuartoEditado", Program.CurrentCulture));
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("RoomNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método para excluir um quarto pelo numero de quarto.
        /// </summary>
        public static void ExcluiQuarto()
        {
            Quarto quartoParaExcluir = null;
            Console.WriteLine(Utility.ResourceHelper.GetString("NumberRoom", Program.CurrentCulture));
            int numeroQuarto = int.Parse(Console.ReadLine().Trim());

            foreach (var quarto in Quarto.ListaQuartos)
            {
                if (quarto.QuartoNumero == numeroQuarto)
                {
                    quartoParaExcluir = quarto;
                    break;
                }
            }

            if (quartoParaExcluir != null)
            {
                Quarto.ListaQuartos.Remove(quartoParaExcluir);
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("QuartoExcluido", Program.CurrentCulture), numeroQuarto);
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("RoomNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método que procura um quarto pelo número informado.
        /// </summary>
        /// <param name="numeroquarto">O numero do quarto.</param>
        /// <returns></returns>
        internal static Quarto EncontrarQuartoNumero(int numeroquarto)
        {
            
            Quarto? quartoEncontrado = Quarto.ListaQuartos.Find(u => u is Quarto && u.QuartoNumero == numeroquarto) as Quarto;
            
            return quartoEncontrado;
        }

        /// <summary>
        /// Método que lista os quartos disponíveis nas datas informadas.
        /// </summary>
        /// <param name="dataInicio">A data de ínicio.</param>
        /// <param name="dataFim">A data de fim.</param>
        /// <returns></returns>
        public static bool ListarQuartosDisponiveis(DateTime dataInicio, DateTime dataFim)
        {
            Console.WriteLine(Utility.ResourceHelper.GetString("AvailableRooms", Program.CurrentCulture), dataInicio.ToString("dd/MM/yyyy"), dataFim.ToString("dd/MM/yyyy"));
            bool nenhum = false;

            foreach (var quarto in Quarto.ListaQuartos)
            {
                if (quarto.EstaDisponivel(dataInicio, dataFim))
                {
                    Console.WriteLine(Utility.ResourceHelper.GetString("InfoRooms", Program.CurrentCulture),
                        quarto.Hotel.HotelREF, quarto.QuartoNumero, quarto.QuartoTipo, quarto.QuartoDescricao, quarto.QuartoDiaria, quarto.QuartoCapacidade);
                    nenhum = true;
                }
            }

            if (nenhum == false)
                Console.WriteLine(Utility.ResourceHelper.GetString("NoRooms", Program.CurrentCulture));

            return nenhum;
        }
    }
    #endregion
}
