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
    /// Classe base que representa utilizador em um sistema de gestão de alocamentos turísticos.
    /// </summary>
    abstract public class Utilizador
    {
        #region ATRIBUTOS
        private int UtilizadorId;
        private static int proximoutilizadorid = 1;
        private string UtilizadorUsername;
        private string UtilizadorPassword;
        private string UtilizadorName;
        private string UtilizadorTipo;
        #endregion

        #region PROPRIEDADES
        public int IdUtilizador
        {
            get { return UtilizadorId; }
            set { UtilizadorId = value; }
        }

        public string UsernameUtilizador
        {
            get { return UtilizadorUsername; }
            protected set { UtilizadorUsername = value; }
        }

        public string PasswordUtilizador
        {
            get { return UtilizadorPassword; }
            protected set { UtilizadorPassword = value; }
        }

        public string NameUtilizador
        {
            get { return UtilizadorName; }
           protected set { UtilizadorName = value; }
        }

        public string TypeUtilizador
        {
            get { return UtilizadorTipo; }
          protected  set { UtilizadorTipo = value; }
        }
        #endregion

        #region CONSTRUTORES

        /// <summary>
        /// Inicializa uma nova instancia da classe Utilizador com valores padrões <see cref="Utilizador"/>.
        /// </summary>
        public Utilizador()
        {
            UtilizadorId = 1;
            UtilizadorUsername = "";
            UtilizadorPassword = "";
            UtilizadorName = "";
            UtilizadorTipo = "";
        }

        /// <summary>
        /// Inicializa uma nova instancia da classe Utilizador com valores especificos <see cref="Utilizador"/>.
        /// </summary>
        /// <param name="username">The username.</param>
        /// <param name="password">The password.</param>
        /// <param name="name">The name.</param>
        /// <param name="type">The type.</param>
        public Utilizador(string username, string password, string name, string type)
        {
            IdUtilizador = proximoutilizadorid++;
            UsernameUtilizador = username;
            PasswordUtilizador = password;
            NameUtilizador = name;
            TypeUtilizador = type;
        }
        #endregion

        #region MÉTODOS

        #endregion
    }
}