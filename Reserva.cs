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
using System.Runtime.InteropServices;
using System.Data;
using System.Resources;
using static GestaoAlojamentoTuristico.Utility;
using static GestaoAlojamentoTuristico.Reserva;

namespace GestaoAlojamentoTuristico
{
    /// <summary>
    /// Classe que representa as reservas no sistema de gerenciamento de alocamentos turisticos.
    /// </summary>
    internal class Reserva
    {
        public static List<Reserva> ListaReservas = new List<Reserva>();
        List<Quarto> quartos = Quarto.ListaQuartos;

        #region ATRIBUTOS
        private int IdReserva;
        private static int proximoidreserva = 1;
        private int IdQuarto;
        private DateTime InicioReserva;
        private DateTime FimReserva;
        private DateTime CheckIn;
        private DateTime CheckOut;
        private decimal DiariaQuarto;
        private decimal PrecoTotal;
        private Hospede? hospedeAtual;
        private Hotel? hotelAtual;
        private Quarto? quartoAtual;
        private StatusReserva estadoReserva;
        public enum StatusReserva
        {
            Confirmada,
            Pendente,
            Cancelada,
            Concluida
        }
        #endregion

        #region PROPRIEDADES
        public int ReservaId
        {
            get { return IdReserva; }
            set { IdReserva = value; }
        }
        public int QuartoId
        {
            get { return IdQuarto; }
            set { IdQuarto = value; }
        }
        public DateTime ReservaInicio
        {
            get { return InicioReserva; }
            set { InicioReserva = value; }
        }
        public DateTime ReservaFim
        {
            get { return FimReserva; }
            set { FimReserva = value; }
        }
        public DateTime InCheck
        {
            get { return CheckIn; }
            set { CheckIn = value; }
        }
        public DateTime OutCheck
        {
            get { return CheckOut; }
            set { CheckOut = value; }
        }
        public decimal PerNight
        {
            get { return DiariaQuarto; }
            set { DiariaQuarto = value; }
        }
        public decimal TotalCost
        {
            get { return PrecoTotal; }
            set { PrecoTotal = value; }
        }
        public StatusReserva EstadoReserva
        {
            get { return estadoReserva; } 
            set { estadoReserva = value; }
        }
        public Hospede HospedeAtual { get; set; }
        public Hotel HotelAtual { get; set; }
        public Quarto QuartoAtual { get; set; }
        
        #endregion

        #region CONSTRUTORES        
        /// <summary>
        /// Inicializa uma nova instancia da classe Reserva com valores padrões <see cref="Reserva"/>.
        /// </summary>
        public Reserva()
        {
            IdReserva = 1;
            DiariaQuarto = 0;
            PrecoTotal = 0;
            estadoReserva = StatusReserva.Confirmada;
            hospedeAtual = null;
            hotelAtual = null;
            quartoAtual = null;
        }

        /// <summary>
        /// Inicializa uma nova instancia da classe Reserva com valores especificos <see cref="Reserva"/>.
        /// </summary>
        /// <param name="precototal">The precototal.</param>
        /// <param name="estadoreserva">The estadoreserva.</param>
        /// <param name="hospede">The hospede.</param>
        public Reserva(DateTime inicio, DateTime fim, DateTime checkin, DateTime checkout, decimal precototal, StatusReserva estadoreserva, Hospede hospede, Hotel hotel, Quarto quarto)
        {
            ReservaId = proximoidreserva++;
            ReservaInicio = inicio;
            ReservaFim = fim;
            InCheck = checkin;
            OutCheck = checkout;
            PrecoTotal = precototal;
            estadoReserva = estadoreserva;
            HospedeAtual = hospede;
            HotelAtual = hotel;
            QuartoAtual = quarto;
        }
        #endregion
    }

    /// <summary>
    /// Classe responsável por gerir as reservas no sistema de gerenciamento de alocamentos turisticos.
    /// </summary>
    public class GestaoReserva
    {
        #region MÉTODOS

        /// <summary>
        /// Método para criar uma nova reserva com base nas informações fornecidas pelo usuário.
        /// </summary>
        public static void CriaReserva()
        {
            DateTime dataAtual = Utility.dataAtual;

            string checkin = "01/01/1010";
            DateTime datacheckin = DateTime.ParseExact(checkin, "dd/MM/yyyy", CultureInfo.InvariantCulture);
            string checkout = "01/01/1010";
            DateTime datacheckout = DateTime.ParseExact(checkout, "dd/MM/yyyy", CultureInfo.InvariantCulture);

            Console.WriteLine(Utility.ResourceHelper.GetString("StartDate", Program.CurrentCulture));
            string inicio = Console.ReadLine().Trim();
            DateTime datainicio = DateTime.ParseExact(inicio, "dd/MM/yyyy", CultureInfo.InvariantCulture);

            Console.WriteLine(Utility.ResourceHelper.GetString("EndDate", Program.CurrentCulture));
            string fim = Console.ReadLine().Trim();
            DateTime datafim = DateTime.ParseExact(fim, "dd/MM/yyyy", CultureInfo.InvariantCulture);

            if (datainicio < dataAtual || datafim < dataAtual || datainicio == datafim)
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("ValidDate", Program.CurrentCulture));
                return;
            }

            GestaoQuarto.ListarQuartosDisponiveis(datainicio, datafim);

            Console.WriteLine(Utility.ResourceHelper.GetString("NumberRoom", Program.CurrentCulture));
            int quartoid = int.Parse(Console.ReadLine().Trim());

            Quarto quartoSelecionado = GestaoQuarto.EncontrarQuartoNumero(quartoid);

            decimal precoTotal = CalcularPrecoTotal(datainicio, datafim, quartoSelecionado.QuartoNumero);
            Console.WriteLine(Utility.ResourceHelper.GetString("TotalCost",Program.CurrentCulture), precoTotal);

            Console.WriteLine(Utility.ResourceHelper.GetString("NIFHospede", Program.CurrentCulture));
            int NIF = int.Parse(Console.ReadLine().Trim());

            Hospede hospedeSelecionado = Hospede.EncontrarHospedeId(NIF);

            Console.WriteLine(Utility.ResourceHelper.GetString("RefHotel", Program.CurrentCulture));
            int REF = int.Parse(Console.ReadLine().Trim());

            Hotel HotelSelecionado = Hotel.EncontrarHotelRef(REF);

            if (hospedeSelecionado != null)
            {
                ListaReservas.Add(new Reserva(datainicio, datafim, datacheckin, datacheckout, precoTotal, StatusReserva.Confirmada, hospedeSelecionado, HotelSelecionado, quartoSelecionado));
                Utility.SalvarReservasEmArquivo();
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("ReservaCriada", Program.CurrentCulture));
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("HospedeNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método que edita uma reserva de um hospede restringido pelo seu identificador.
        /// </summary>
        /// <param name="NIFHospede">O identificador do hospede</param>
        public static void EditaReserva(int NIFHospede)
        {
            DateTime dataAtual = Utility.dataAtual;

            Console.WriteLine(Utility.ResourceHelper.GetString("IdReserva", Program.CurrentCulture));
            int IdReservaEdit = int.Parse(Console.ReadLine().Trim());

            Reserva ReservaEdit = ListaReservas.Find(u => u.ReservaId == IdReservaEdit);

            if (ReservaEdit != null)
            {
                if (NIFHospede == ReservaEdit.HospedeAtual.HospedeNIF)
                {
                    Console.WriteLine(Utility.ResourceHelper.GetString("StartDate", Program.CurrentCulture));
                    string novaDataInicioString = Console.ReadLine().Trim();

                    Console.WriteLine(Utility.ResourceHelper.GetString("EndDate", Program.CurrentCulture));
                    string novaDataFimString = Console.ReadLine().Trim();

                    DateTime.TryParseExact(novaDataInicioString, "dd/MM/yyyy HH:mm", CultureInfo.InvariantCulture, DateTimeStyles.None, out DateTime novaDataInicio);
                    DateTime.TryParseExact(novaDataFimString, "dd/MM/yyyy HH:mm", CultureInfo.InvariantCulture, DateTimeStyles.None, out DateTime novaDataFim);

                    if (novaDataInicio < dataAtual || novaDataFim < dataAtual)
                    {
                        Console.Clear();
                        Console.WriteLine(Utility.ResourceHelper.GetString("ValidDate", Program.CurrentCulture));
                        return;
                    }

                    if (DateTime.TryParseExact(novaDataInicioString, "dd/MM/yyyy HH:mm", CultureInfo.InvariantCulture, DateTimeStyles.None, out DateTime novaDataFimReserva) &&
                        DateTime.TryParseExact(novaDataFimString, "dd/MM/yyyy HH:mm", CultureInfo.InvariantCulture, DateTimeStyles.None, out DateTime novaDataInicioReserva))
                    {
                        ReservaEdit.ReservaInicio = novaDataInicioReserva;
                        ReservaEdit.ReservaFim = novaDataFimReserva;
                        Console.Clear();
                        Console.WriteLine(Utility.ResourceHelper.GetString("ReservaEditada", Program.CurrentCulture));
                    }
                    else
                    {
                        Console.Clear();
                        Console.WriteLine(Utility.ResourceHelper.GetString("ValidDate", Program.CurrentCulture));
                    }
                }
                else
                {

                }
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("ReservaNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método para cancelar uma reserva de um hospede restringido pelo seu identificador.
        /// </summary>
        /// <param name="NIFHospede">O identificador do hospede.</param>
        public static void CancelaReserva(int NIFHospede)
        {
            Console.WriteLine(Utility.ResourceHelper.GetString("IdReserva", Program.CurrentCulture));
            int IdReserva = int.Parse(Console.ReadLine().Trim());

            Reserva CancelaReservaEdit = ListaReservas.Find(u => u.ReservaId == IdReserva);

            if (CancelaReservaEdit != null)
            {
                if (NIFHospede == CancelaReservaEdit.HospedeAtual.HospedeNIF)
                {
                    StatusReserva novoEstado = StatusReserva.Cancelada;
                    CancelaReservaEdit.EstadoReserva = novoEstado;
                    Console.Clear();
                    Console.WriteLine(Utility.ResourceHelper.GetString("ReservaCancelada", Program.CurrentCulture), IdReserva);
                }
                else
                {

                }
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("ReservaNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método para calcular o preço total da estadia.
        /// </summary>
        /// <param name="dataInicio">A data de inicio.</param>
        /// <param name="dataFim">A data de fim.</param>
        /// <param name="quartonumero">O numero do quarto.</param>
        /// <returns></returns>
        public static decimal CalcularPrecoTotal(DateTime dataInicio, DateTime dataFim, int quartonumero)
        {
            Quarto quarto = Quarto.ListaQuartos.FirstOrDefault(q => q.QuartoNumero == quartonumero);

            if (quarto != null)
            {
                TimeSpan duracaoEstadia = dataFim - dataInicio;
                int diasEstadia = duracaoEstadia.Days;

                decimal precoTotal = diasEstadia * quarto.QuartoDiaria;

                return precoTotal;
            }
            else
            {
                throw new InvalidOperationException(ResourceHelper.GetString("QuartoNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método para listar as reservas de um hotel pela sua referência.
        /// </summary>
        /// <param name="REFHotel">O identificador do Hotel.</param>
        public static void ListarReservasPorHotel(int REFHotel)
        {
            Console.WriteLine("+-----------------------------------------+------------------------------------------+");
            Console.Write(Utility.ResourceHelper.GetString("Reservas", Program.CurrentCulture));
            Console.WriteLine("+-----------------------------------------+------------------------------------------+");
            foreach (var reserva in ListaReservas)
            {
                if (reserva.HotelAtual != null && reserva.HotelAtual.HotelREF == REFHotel)
                {
                    string reservationInfo = string.Format(ResourceHelper.GetString("InfoReservaHotel", Program.CurrentCulture),
                        reserva.ReservaId, 
                        reserva.EstadoReserva, 
                        reserva.TotalCost,
                        reserva.ReservaInicio,
                        reserva.ReservaFim,
                        reserva.InCheck,
                        reserva.OutCheck,
                        reserva.HotelAtual.HotelREF,
                        reserva.HotelAtual.NameUtilizador);

                    Console.WriteLine(reservationInfo);
                    Console.WriteLine("+-----------------------------------------+------------------------------------------+");
                }
            }

            if (!ListaReservas.Any(reserva => reserva.HotelAtual != null && reserva.HotelAtual.HotelREF == REFHotel))
            {
                string noreserva = string.Format(ResourceHelper.GetString("ReservaNotFoundHotel", Program.CurrentCulture),
                   REFHotel);
                Console.WriteLine(noreserva);
            }
        }

        /// <summary>
        /// Método para listar as reservas de um hospede pelo seu identificador.
        /// </summary>
        /// <param name="NIFHospede">O identificador do hospede.</param>
        public static void ListarReservasPorHospede(int NIFHospede)
        {
            Console.WriteLine("+-----------------------------------------+------------------------------------------+");
            Console.Write(Utility.ResourceHelper.GetString("Reservas", Program.CurrentCulture));
            Console.WriteLine("+-----------------------------------------+------------------------------------------+");
            foreach (var reserva in ListaReservas)
            {
                if (reserva.HospedeAtual != null && reserva.HospedeAtual.HospedeNIF == NIFHospede)
                {
                    string reservationInfo = string.Format(ResourceHelper.GetString("InfoReserva", Program.CurrentCulture),
                    reserva.ReservaId,
                    reserva.EstadoReserva,
                    reserva.TotalCost,
                    reserva.ReservaInicio,
                    reserva.ReservaFim,
                    reserva.InCheck,
                    reserva.OutCheck,
                    reserva.HospedeAtual.HospedeNIF,
                    reserva.HospedeAtual.NameUtilizador,
                    reserva.HotelAtual.HotelREF);

                    Console.WriteLine(reservationInfo);
                    Console.WriteLine("+-----------------------------------------+------------------------------------------+");
                }
            }

            if (!ListaReservas.Any(reserva => reserva.HospedeAtual != null && reserva.HospedeAtual.HospedeNIF == NIFHospede))
            {
                string noreserva = string.Format(ResourceHelper.GetString("ReservaNotFoundHospede", Program.CurrentCulture),
                   NIFHospede);
                Console.WriteLine(noreserva);
            }
        }
        #endregion
    }
}