'''
cd pset8
cd finance
export API_KEY=pk_444aa5fb2eab42208c2479834ec6944f
flask run
'''
import os
#import uuid #for id  

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure name was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares", 403)
        
        elif not request.form.get("shares")>0:
            return apology("must provide positive integer", 403)
            
        check=lookup(request.form.get("symbol"))
        
        if check==None:
            return apology("symbol does not exist", 403)
        else:
            name=check["name"]
            price=check["price"]
            symbol=check["symbol"]
        
        # Query database for username
        row = db.execute("SELECT cash FROM users WHERE id=ses",
                          ses=session['user_id'])

        # Ensure username exists and password is correct
        if len(rows) != 1:
            return apology("something go wrong", 403)
            
        if prince>row[0]:
            return apology("not enough cash", 403)

        return apology("good", 403) #END NOW
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")
    #return apology("TODO")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        check=lookup(request.form.get("symbol"))
        
        if check==None:
            return apology("oł noł", 403)
        else:
            name=check["name"]
            price=check["price"]
            symbol=check["symbol"]
            #return apology(name, 403)
        
        return render_template("quoted.html", name=name, price=price, symbol=symbol)
        # Redirect user to next page quoted
        
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username you want", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
            
        # Ensure password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 403)
            
        # Ensure password is the same
        if not request.form.get("password")==request.form.get("confirmation"):
            return apology("password must be the same", 403)

        # Check if user exist 
        checkUser = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(checkUser) !=0:
            return apology("User exist")
        
        
        # Ensure username not exists and password is correct
        #NOT 
        #if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
         #   return apology("invalid username and/or password", 403)
        
        hash_password=generate_password_hash(request.form.get("password"))
        
        db.execute("INSERT INTO users ( username, hash) VALUES( ?, ?)",  request.form.get("username"), hash_password)

        #sql = "INSERT INTO customers (name, address) VALUES (%s, %s)"
        #val = ("John", "Highway 21")
        #mycursor.execute(sql, val)
#hash uuid.uuid1(),
        # Redirect user to home page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
