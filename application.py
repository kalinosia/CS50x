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

bought=False
sold=False

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #get date what user have from owners table 
    rows=db.execute("SELECT symbol, shares FROM owners WHERE user_id=:id", id=session['user_id'])
    #all cash what user have and earn
    totalAll=0
    ''' NOT
    if len(rows) !=0:
        for row in rows:    
            symbol=str(row["symbol"])
            shares=int(row["shares"])
            check=lookup(symbol)
            price=float(check["price"])
            name=str(check["name"])
            total=float(price*shares) 
            totalAll+=total
    '''
    #make dictionaries
    check={}
    #check if owner have something, add to dictionaries lookup function to each row (each symbol), and add cash
    if len(rows) !=0:
        for row in rows:
            check[row["symbol"]] = (lookup(row["symbol"]))
            #check={row["symbol"]: (lookup(row["symbol"]))} that u dont add :D
            totalAll+=(float(check.get(row["symbol"])["price"])*(row["shares"]))
     
    #find out cash what user have to spend
    cashrow=db.execute("SELECT cash FROM users WHERE id=:id", id=session['user_id'])
    cash=cashrow[0]["cash"]
    #and add that cash to cash shares value
    totalAll+=cash
    #return value to reander each row in table in index.html
    return render_template("index.html",   check=check, rows=rows, cash=cash, totalAll=totalAll)
    ##return apology("TODO")


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
            
        shares=request.form.get("shares")
        #return apology(shares)
        shares=int(shares)
        
        if  shares <= 0:
            return apology("must provide positive integer", 403)
        
        check=lookup(request.form.get("symbol"))
        
        if check==None:
            return apology("symbol does not exist", 403)
        else:
            name=check["name"]
            price=check["price"]
            symbol=check["symbol"]
        
        # Query database for username
        row = db.execute("SELECT * FROM users WHERE id=:ses",
                                                            ses=session['user_id'])
        
        # Ensure username exists and password is correct
        if len(row) != 1:
            return apology("something go wrong", 403)
        
        cash=row[0]["cash"]   #numeric (precision, scale) 
        
        if  price*shares > cash:
            return apology("not enough cash", 403)
        
        #start buy
        
        #TABLE HISTORY UPADATE
        db.execute("INSERT INTO history ( user_id, symbol, name, price, shares) VALUES( ?, ?, ?, ?, ?)",  
        session['user_id'], symbol, name, price, shares)
        
        #USERS UPADE CASH
        db.execute("UPDATE users SET cash = :hajs WHERE id=:ses",
                                                            ses=session['user_id'], hajs=cash-(price*shares))
        #OWNED UPDATE
        exist=db.execute("SELECT * FROM owners WHERE user_id=:id and symbol=:symbol",
                                                id=session['user_id'], symbol=symbol)
        if len(exist)!=0:
            before_shares_rows=db.execute("SELECT shares FROM owners WHERE user_id=:id and symbol=:symbol",
                                                id=session['user_id'], symbol=symbol)
            before_shares=before_shares_rows[0]["shares"]
            db.execute("UPDATE owners SET shares=:share WHERE user_id=:id and symbol=:symbol",
                                            share=int(before_shares)+int(request.form.get("shares")), id=session['user_id'], symbol=symbol)
        else:
            db.execute("INSERT INTO owners ( user_id, symbol, shares) VALUES( ?, ?, ?)",  
                                                            session['user_id'], symbol, shares)
        
        return redirect("/")
        
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")
    

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    rows=db.execute("SELECT * FROM history WHERE user_id=:id", id=session['user_id'])
    
    return render_template("history.html", rows=rows)
    ##return apology("TODO")



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

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        #find symbol
        check=lookup(request.form.get("symbol"))
        #check if exist and find out name & price
        if check==None:
            return apology("oł noł", 403)
        else:
            name=check["name"]
            price=check["price"]
            symbol=check["symbol"]
            #return apology(name, 403)
        #return page with date
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
##########################PERSONAL TOUCH
#if password is corret have numbers letters and symbols#####
        password=request.form.get("password")
        list=[ord(c) for c in password]
        if len(list)<8:
            return apology("Too short password", 403)
        elif len(list)>20:
            return apology("Too long password", 403)
        BigLetter=False
        SmallLetter=False
        SymbolPassword=False
        NumberPassword=False
        for item in list:
            if item>64 and item<91:
                BigLetter=True
            elif item>96 and item<123:
                SmallLetter=True
            elif (item>32 and item<48)or(item>57 and item<65)or(item>90 and item<97)or(item>122 and item<127):
                SymbolPassword=True
            elif item>47 and item<58:
                NumberPassword=True
        if BigLetter==False or SmallLetter==False or SymbolPassword==False or NumberPassword==False:
            return apology("In password must exist big and small letter, number and symbol!", 403)
#####################################/
        # Check if user exist 
        checkUser = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(checkUser) !=0:
            return apology("User exist")
        #make password not to read
        hash_password=generate_password_hash(request.form.get("password"))
        #add user to users table
        db.execute("INSERT INTO users ( username, hash) VALUES( ?, ?)",  request.form.get("username"), hash_password)

    #sql = "INSERT INTO customers (name, address) VALUES (%s, %s)" # FOR LATER
    #val = ("John", "Highway 21")
    #mycursor.execute(sql, val)
#hash uuid.uuid1() to make unique id.... ??####

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
    if request.method == "POST":

        # Ensure sybol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares", 403)
            
        #shares = shares how many want sell
        shares=request.form.get("shares")
        #return apology(shares) if not positive number 
        shares=int(shares)
        if  shares <= 0:
            return apology("must provide positive integer", 403)
        #find what name, how many cost shares of our symbol
        check=lookup(request.form.get("symbol"))
        #check if symbol exist
        if check==None:
            return apology("symbol does not exist", 403)
        else:
            name=check["name"]
            price=check["price"]
            symbol=check["symbol"]
        
        # Query database to check if user-owner have that symbol 
        row = db.execute("SELECT * FROM owners WHERE user_id=:ses and symbol=:symbol", 
                                                            ses=session['user_id'], symbol=symbol)
        
        # Check is symbol is in owners table - if user own what want sell
        if len(row) != 1:
            return apology("You don't have to sell?", 403)
        #how many share have 
        have_shares=row[0]["shares"]   
        #check if have more share that want sell
        if  have_shares < shares:
            return apology("not enough shares to sell", 403)
        #cash what user have before share (cash=cash before +cash from sells)
        user = db.execute("SELECT * FROM users WHERE id=:ses", 
                                                            ses=session['user_id'])
        cash=user[0]["cash"]
        
        #start buy
        
        #TABLE HISTORY UPADATE
        db.execute("INSERT INTO history ( user_id, symbol, name, price, shares) VALUES( ?, ?, ?, ?, ?)",  
        session['user_id'], symbol, name, price, (-1)*shares)
        
        #USERS UPADE CASH
        db.execute("UPDATE users SET cash = :hajs WHERE id=:ses",
                                                            ses=session['user_id'], hajs=cash+(price*shares))
        #OWNED UPDATE
        db.execute("UPDATE owners SET shares=:share WHERE user_id=:id and symbol=:symbol",
                                            share=int(have_shares)-int(shares), id=session['user_id'], symbol=symbol)
        if have_shares==shares:
            db.execute("DELETE FROM owners  WHERE user_id=:id and symbol=:symbol",
                                             id=session['user_id'], symbol=symbol)
        
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
