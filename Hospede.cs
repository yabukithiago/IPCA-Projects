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
using static GestaoAlojamentoTuristico.Utility;

namespace GestaoAlojamentoTuristico
{
    /// <summary>
    /// Classe derivada que representa hospedes.
    /// </summary>
    /// <seealso cref="GestaoAlojamentoTuristico.Hospede" />
    internal class Hospede : Utilizador
    {
        #region ATRIBUTOS
        public static List<Hospede> ListaHospedes { get; set; } = new List<Hospede>();
        List<Reserva> reservas = Reserva.ListaReservas;
        private int NIFHospede;
        #endregion

        #region PROPRIEDADES
        public int HospedeNIF
        {
            get { return NIFHospede; }
            private set { NIFHospede = value; }
        }
        #endregion

        #region CONSTRUTORES

        /// <summary>
        /// Inicializa uma nova instância da classe Hospede com valores especificos <see cref="Hospede"/>.
        /// </summary>
        /// <param name="NIF">O nif.</param>
        /// <param name="username">O nome de usuário.</param>
        /// <param name="password">A senha.</param>
        /// <param name="nome">O nome.</param>
        /// <param name="tipo">O tipo.</param>
        public Hospede(int NIF, string username, string password, string nome, string tipo) :  base(username, password, nome, tipo)
        {
            HospedeNIF = NIF;
        }
        #endregion

        #region MÉTODOS        

        /// <summary>
        /// Método que representa um menu de um hospede não logado.
        /// </summary>
        public static void Menu_Hospede_Nao_Logado()
        {
            string username, password;

            do
            {
                Console.WriteLine(Utility.ResourceHelper.GetString("LoginHospede", Program.CurrentCulture));

                Console.Write(Utility.ResourceHelper.GetString("Username", Program.CurrentCulture));
                username = Console.ReadLine();

                Console.Write(Utility.ResourceHelper.GetString("Password", Program.CurrentCulture));
                password = Console.ReadLine();

            } while (!Hospede.EfetuarLogin(username, password));
        }

        /// <summary>
        /// Método para efetuar o login na plataforma.
        /// </summary>
        /// <param name="username">O username.</param>a
        /// <param name="password">A password.</param>
        /// <returns></returns>
        public static bool EfetuarLogin(string username, string password)
        {
            foreach (var hosp in ListaHospedes)
            {
                if (hosp.UsernameUtilizador == username && hosp.PasswordUtilizador == password)
                {
                    hosp.Menu_Hospede_Logado();
                    return true;
                }
            }

            Console.Write(Utility.ResourceHelper.GetString("UserNotFound", Program.CurrentCulture));
            string entradaUsuario = Console.ReadLine().Trim();

            if (entradaUsuario.Equals("S", StringComparison.OrdinalIgnoreCase) ||
            entradaUsuario.Equals("Y", StringComparison.OrdinalIgnoreCase) ||
            entradaUsuario.Equals("O", StringComparison.OrdinalIgnoreCase))
            {
                CriaHospede();
            }
            return false;
        }

        /// <summary>
        /// Método para criar um novo hospede e adiciona-lo na lista de hospedes.
        /// </summary>
        /// <returns></returns>
        public static void CriaHospede()
        {
            Console.WriteLine(Utility.ResourceHelper.GetString("NIFHospede", Program.CurrentCulture));
            int NIFHospede = int.Parse(Console.ReadLine());

            Console.WriteLine(Utility.ResourceHelper.GetString("Username", Program.CurrentCulture));
            string UsernameHospede = Console.ReadLine().Trim();

            if (ListaHospedes.Any(h => h.UsernameUtilizador == UsernameHospede))
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("UserExist", Program.CurrentCulture));
                return;
            }

            Console.WriteLine(Utility.ResourceHelper.GetString("Password", Program.CurrentCulture));
            string PasswordHospede = Console.ReadLine().Trim();

            Console.WriteLine(Utility.ResourceHelper.GetString("NameHospede", Program.CurrentCulture));
            string NomeHospede = Console.ReadLine().Trim();

            string TipoHospede = "Hospede";

            ListaHospedes.Add(new Hospede(NIFHospede, UsernameHospede, PasswordHospede, NomeHospede, TipoHospede));
            Utility.SalvarHospedesEmArquivo();
            Console.Clear();
        }

        /// <summary>
        /// Método que representa um menu de um hospede logado.
        /// </summary>
        public void Menu_Hospede_Logado()
        {
            Console.Clear();
            bool continuar = true;

            while (continuar)
            {
                Console.WriteLine("+-------------------------------------------+");
                Console.WriteLine(Utility.ResourceHelper.GetString("MainMenu", Program.CurrentCulture));
                Console.WriteLine("+-------------------------------------------+");
                Console.WriteLine(Utility.ResourceHelper.GetString("Welcome", Program.CurrentCulture), NameUtilizador);
                Console.WriteLine(Utility.ResourceHelper.GetString("ChooseOption", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("RealizeReserva", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("VisualizeReserva", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("EditReserva", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("CancelReserva", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("RealizeCheckIn", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("RealizeCheckOut", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("EditInformations", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("DeleteAccount", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("RealizeLogout", Program.CurrentCulture));
                Console.WriteLine("+-------------------------------------------+");

                int escolha = int.Parse(Console.ReadLine());

                switch (escolha)
                {
                    case 1:
                        Console.Clear();
                        GestaoReserva.CriaReserva();
                        break;
                    case 2:
                        Console.Clear();
                        GestaoReserva.ListarReservasPorHospede(NIFHospede);
                        break;
                    case 3:
                        Console.Clear();
                        GestaoReserva.EditaReserva(NIFHospede);
                        break;
                    case 4:
                        Console.Clear();
                        GestaoReserva.CancelaReserva(NIFHospede);
                        break;
                    case 5:
                        Console.Clear();
                        FazerCheckIn(NIFHospede);
                        break;
                    case 6:
                        Console.Clear();
                        FazerCheckOut(NIFHospede);
                        break;
                    case 7:
                        Console.Clear();
                        EditaHospede();
                        break;
                    case 8:
                        Console.Clear();
                        ExcluiHospede(NameUtilizador);
                        continuar = false;
                        break;
                    case 10:
                        continuar = false;
                        Console.WriteLine(Utility.ResourceHelper.GetString("Logout", Program.CurrentCulture));
                        break;
                    default:
                        Console.WriteLine(Utility.ResourceHelper.GetString("Option", Program.CurrentCulture));
                        break;
                }
            }
        }

        /// <summary>
        /// Método para editar um hospede.
        /// </summary>
        public static void EditaHospede()
        {
            Console.WriteLine(Utility.ResourceHelper.GetString("Username", Program.CurrentCulture));
            string UsernameHospedeEdit = Console.ReadLine().Trim();

            Hospede HospedeEdit = ListaHospedes.Find(u => u.NameUtilizador == UsernameHospedeEdit && u.TypeUtilizador == "Hospede");

            if (HospedeEdit != null)
            {
                Console.WriteLine(Utility.ResourceHelper.GetString("NewNameHospede", Program.CurrentCulture));
                HospedeEdit.NameUtilizador = Console.ReadLine().Trim();

                Utility.SalvarHospedesEmArquivo();
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("HospedeEdit", Program.CurrentCulture));
            }
            else
            {
                Console.Clear();
                Console.WriteLine("HospedeNotFound");
            }
        }

        /// <summary>
        /// Método que exclui um hospede.
        /// </summary>
        /// <param name="nome">O nome.</param>
        public static void ExcluiHospede(string nome)
        {
            Hospede DeleteHospede = null;

            foreach (var hospede in ListaHospedes)
            {
                if (hospede.NameUtilizador == nome)
                {
                    DeleteHospede = (Hospede)hospede;
                    break;
                }
            }

            if (DeleteHospede != null)
            {
                ListaHospedes.Remove(DeleteHospede);
                Utility.SalvarHospedesEmArquivo();
                Console.Clear();
                string hospede = string.Format(ResourceHelper.GetString("DeleteHospede", Program.CurrentCulture), nome);
                Console.WriteLine(hospede);
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("HospedeNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método para encontrar o hospede pelo identificador.
        /// </summary>
        /// <param name="NIF">O identificador do hospede.</param>
        /// <returns></returns>
        internal static Hospede EncontrarHospedeId(int NIF)
        {
            Hospede? hospedeEncontrado = ListaHospedes.Find(u => u is Hospede && u.HospedeNIF == NIF) as Hospede;

            return hospedeEncontrado;
        }

        /// <summary>
        /// Método que realiza o check-in.
        /// </summary>
        /// <param name="NIFHospede">O identificador do hospede.</param>
        public static void FazerCheckIn(int NIFHospede)
        {
            DateTime dataCheckIn = DateTime.Now;

            Console.WriteLine(Utility.ResourceHelper.GetString("CheckInReserva", Program.CurrentCulture));
            int idReserva = int.Parse(Console.ReadLine().Trim());

            var reserva = Reserva.ListaReservas.FirstOrDefault(r => r.ReservaId == idReserva);

            if (reserva != null && reserva.EstadoReserva == Reserva.StatusReserva.Confirmada)
            {
                if (NIFHospede == reserva.HospedeAtual.HospedeNIF)
                {
                    reserva.EstadoReserva = Reserva.StatusReserva.Pendente;
                    reserva.InCheck = dataCheckIn;
                    Utility.SalvarReservasEmArquivo();
                    Console.Clear();
                    string checkin = string.Format(ResourceHelper.GetString("Check-In", Program.CurrentCulture), dataCheckIn, idReserva);
                    Console.WriteLine(checkin);
                }
                else
                {
                    Console.WriteLine(Utility.ResourceHelper.GetString("ErroCheck-In", Program.CurrentCulture), idReserva);
                }
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("ErroCheck-In", Program.CurrentCulture), idReserva);
            }
        }

        /// <summary>
        /// Método que realiza o check-out.
        /// </summary>
        /// <param name="NIFHospede">O identificador do hospede.</param>
        public static void FazerCheckOut(int NIFHospede)
        {
            DateTime dataCheckOut = DateTime.Now;

            Console.WriteLine(Utility.ResourceHelper.GetString("CheckInReserva", Program.CurrentCulture));
            int idReserva = int.Parse(Console.ReadLine().Trim());

            var reserva = Reserva.ListaReservas.FirstOrDefault(r => r.ReservaId == idReserva);

            if (reserva != null && reserva.EstadoReserva == Reserva.StatusReserva.Pendente)
            {
                if (NIFHospede == reserva.HospedeAtual.HospedeNIF)
                {
                    reserva.EstadoReserva = Reserva.StatusReserva.Concluida;
                    reserva.OutCheck = dataCheckOut;
                    Utility.SalvarReservasEmArquivo();
                    Console.Clear();
                    string checkout = string.Format(ResourceHelper.GetString("Check-Out", Program.CurrentCulture), dataCheckOut, idReserva);
                    Console.WriteLine(checkout);
                }
                else
                {
                    Console.WriteLine(Utility.ResourceHelper.GetString("ErroCheck-Out", Program.CurrentCulture), idReserva);
                }
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("ErroCheck-Out", Program.CurrentCulture), idReserva);
            }
        }
        #endregion
    }
}
