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
    /// Classe derivada que representa hoteis.
    /// </summary>
    /// <seealso cref="GestaoAlojamentoTuristico.Utilizador" />
    internal class Hotel : Utilizador
    {
        #region ATRIBUTOS
        public static List<Hotel> ListaHoteis { get; set; } = new List<Hotel>();
        private int RefHotel;
        #endregion

        #region PROPRIEDADES
        public int HotelREF
        {
            get { return RefHotel; }
            private set { RefHotel = value; }
        }
        #endregion

        #region CONSTRUTORES

        /// <summary>
        /// Inicializa uma nova instancia da classe Hotel com valores especificios <see cref="Hotel"/>.
        /// </summary>
        /// <param name="username">O username.</param>
        /// <param name="password">A password.</param>
        /// <param name="nome">O nome.</param>
        /// <param name="tipo">O tipo.</param>
        public Hotel(int REF, string username, string password, string nome,  string tipo) : base(username, password, nome, tipo)
        {
            HotelREF = REF;
        }
        #endregion

        #region MÉTODOS

        /// <summary>
        /// Método que representa um menu de um hotel não logado.
        /// </summary>
        public static void Menu_Hotel_Nao_Logado()
        {
            string username, password;

            do
            {
                Console.WriteLine(Utility.ResourceHelper.GetString("LoginHotel", Program.CurrentCulture));

                Console.Write(Utility.ResourceHelper.GetString("Username", Program.CurrentCulture));
                username = Console.ReadLine();

                Console.Write(Utility.ResourceHelper.GetString("Password", Program.CurrentCulture));
                password = Console.ReadLine();

            } while (!Hotel.EfetuarLogin(username, password));
        }

        /// <summary>
        /// Método para efetuar o login na plataforma.
        /// </summary>
        /// <param name="username">O username.</param>
        /// <param name="password">A password.</param>
        /// <returns></returns>
        public static bool EfetuarLogin(string username, string password)
        {
            foreach (var hotel in ListaHoteis)
            {
                if (hotel.UsernameUtilizador == username && hotel.PasswordUtilizador == password)
                {
                    hotel.Menu_Hotel_Logado();
                    return true;
                }
            }

            Console.Write(Utility.ResourceHelper.GetString("UserNotFound", Program.CurrentCulture));
            string entradaUsuario = Console.ReadLine().Trim();

            if (entradaUsuario.Equals("S", StringComparison.OrdinalIgnoreCase) ||
            entradaUsuario.Equals("Y", StringComparison.OrdinalIgnoreCase) ||
            entradaUsuario.Equals("O", StringComparison.OrdinalIgnoreCase))
            {
                string SenhaCriacaoHotel = "123ADMIN";

                Console.WriteLine(Utility.ResourceHelper.GetString("SenhaHotel", Program.CurrentCulture));

                string senhaCriacao = Console.ReadLine();
                if (senhaCriacao != SenhaCriacaoHotel)
                {
                    Console.WriteLine(Utility.ResourceHelper.GetString("SenhaHotelErro", Program.CurrentCulture));
                    return false;
                }
                CriaHotel();
            }
            return false;
        }

        /// <summary>
        /// Método para criar um novo hotel e adiciona-lo na lista de hotel.
        /// </summary>
        public static void CriaHotel()
        {
            Console.WriteLine(Utility.ResourceHelper.GetString("RefHotel", Program.CurrentCulture));
            int REF = int.Parse(Console.ReadLine());

            Console.WriteLine(Utility.ResourceHelper.GetString("Username", Program.CurrentCulture));
            string UsernameHotel = Console.ReadLine().Trim();

            if (ListaHoteis.Any(h => h.UsernameUtilizador == UsernameHotel))
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("UserExist", Program.CurrentCulture));
                return;
            }

            Console.WriteLine(Utility.ResourceHelper.GetString("Password", Program.CurrentCulture));
            string PasswordHotel = Console.ReadLine().Trim();

            Console.WriteLine(Utility.ResourceHelper.GetString("NameHotel", Program.CurrentCulture));
            string NomeHotel = Console.ReadLine().Trim();

            string TipoHotel = "Hotel";
            
            ListaHoteis.Add(new Hotel(REF, UsernameHotel, PasswordHotel, NomeHotel, TipoHotel));
            Utility.SalvarHotelEmArquivo();
            Console.Clear();
        }

        /// <summary>
        /// Método que representa um menu de um hotel logado.
        /// </summary>
        public void Menu_Hotel_Logado()
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
                Console.WriteLine(Utility.ResourceHelper.GetString("CreateRoom", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("EditRoom", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("DeleteRoom", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("CancelReserva", Program.CurrentCulture));
                Console.WriteLine(Utility.ResourceHelper.GetString("VisualizeReservaHotel", Program.CurrentCulture));
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
                        GestaoQuarto.CriaQuarto();
                        break;
                    case 2:
                        Console.Clear();
                        GestaoQuarto.EditaQuarto();
                        break;
                    case 3:
                        Console.Clear();
                        GestaoQuarto.ExcluiQuarto();
                        break;
                    case 4:
                        Console.Clear();
                        GestaoReserva.CancelaReserva(HotelREF);
                        break;
                    case 5:
                        Console.Clear();
                        GestaoReserva.ListarReservasPorHotel(HotelREF);
                        break;
                    case 6:
                        Hospede.FazerCheckOut(HotelREF);
                        break;
                    case 7:
                        EditaHotel(NameUtilizador);
                        break;
                    case 8:
                        ExcluiHotel(NameUtilizador);
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
        /// Método para editar um hotel pelo seu nome.
        /// </summary>
        /// <param name="nome">O nome informado.</param>
        public static void EditaHotel(string nome)
        {

            Hotel hotelEdit = ListaHoteis.Find(hotel => hotel.NameUtilizador == nome && hotel.TypeUtilizador == "Hotel");

            if (hotelEdit != null)
            {
                Console.WriteLine(Utility.ResourceHelper.GetString("NewNameHotel", Program.CurrentCulture));
                hotelEdit.NameUtilizador = Console.ReadLine().Trim();

                Utility.SalvarHotelEmArquivo();
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("HotelEdit", Program.CurrentCulture));
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("HotelNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método que exclui um hotel pelo seu nome.
        /// </summary>
        /// <param name="nome">O nome.</param>
        public static void ExcluiHotel(string nome)
        {
            Hotel DeleteHotel = null;

            foreach (var hotel in ListaHoteis)
            {
                if (hotel.NameUtilizador == nome)
                {
                    DeleteHotel = (Hotel)hotel;
                    break;
                }
            }

            if (DeleteHotel != null)
            {
                ListaHoteis.Remove(DeleteHotel);
                Utility.SalvarHotelEmArquivo();
                Console.Clear();
                string hotel = string.Format(ResourceHelper.GetString("DeleteHotel", Program.CurrentCulture), nome);
                Console.WriteLine(hotel);
            }
            else
            {
                Console.Clear();
                Console.WriteLine(Utility.ResourceHelper.GetString("HoteleNotFound", Program.CurrentCulture));
            }
        }

        /// <summary>
        /// Método que encontra um hotel pela referência informada.
        /// </summary>
        /// <param name="REF">A referência informada.</param>
        /// <returns>Retorna o Hotel encontrado.</returns>
        internal static Hotel EncontrarHotelRef(int REF)
        {
            Hotel? hotelEncontrado = ListaHoteis.Find(u => u is Hotel && u.HotelREF == REF) as Hotel;

            return hotelEncontrado;
        }
        #endregion
    }
}
