using System.Xml.Linq;
using static System.Net.Mime.MediaTypeNames;
using System.Collections.Generic;
using System.Globalization;
using System.Resources;
using System.Security.Cryptography.X509Certificates;
using System.Transactions;
using static GestaoAlojamentoTuristico.Utility;

namespace GestaoAlojamentoTuristico
{
    internal class Program
    {
        public static string CurrentCulture { get; set; } = "pt-PT";
        static void Main()
        {
            Utility.CarregarHoteisEmArquivo();
            Utility.CarregarHospedesEmArquivo();
            Utility.CarregarQuartosEmArquivo();
            Utility.CarregarReservasEmArquivo();

            bool running = true;

            int tipo;

            while (running)
            {
                Console.Clear();
                Console.WriteLine("Selecione o seu idioma:");
                Console.WriteLine("1. Portuguese");
                Console.WriteLine("2. English");
                Console.WriteLine("3. Français");
                Console.WriteLine("4. Español");
                Console.WriteLine("5. Sair do programa");
                int language = int.Parse(Console.ReadLine().Trim());

                switch (language)
                {
                    case 1:
                        CurrentCulture = "pt-PT";
                        tipo = ShowLoginMenu();
                        break;
                    case 2:
                        CurrentCulture = "en-US";
                        tipo = ShowLoginMenu();
                        break;
                    case 3:
                        CurrentCulture = "fr-FR";
                        tipo = ShowLoginMenu();
                        break;
                    case 4:
                        CurrentCulture = "es-ES";
                        tipo = ShowLoginMenu();
                        break;
                    case 5:
                        running = false;
                        break;
                    default:
                        Console.WriteLine(ResourceHelper.GetString("Option", CurrentCulture));
                        break;
                }
            }
        }

        static int ShowLoginMenu()
        {
            Console.Clear();
            Console.WriteLine(ResourceHelper.GetString("HelloMessage", CurrentCulture));
            Console.WriteLine(ResourceHelper.GetString("LoginOptions", CurrentCulture));

            int tipo = int.Parse(Console.ReadLine().Trim());

            switch (tipo)
            {
                case 1:
                    Console.Clear();
                    Hospede.Menu_Hospede_Nao_Logado();
                    break;

                case 2:
                    Console.Clear();
                    Hotel.Menu_Hotel_Nao_Logado();
                    break;

                case 3:
                    Console.Clear();
                    Console.WriteLine(ResourceHelper.GetString("ExitingProgramMessage", CurrentCulture));
                    break;

                default:
                    Console.WriteLine(ResourceHelper.GetString("Option", CurrentCulture));
                    break;
            }

            return tipo;
        }
    }
}