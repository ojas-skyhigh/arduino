
import discord
from discord.ext import commands, tasks
from itertools import cycle
import random
import time
import re
import json
import urllib.parse, urllib.request, re

def get_prefix(client, message):
    with open("prefixes.json", 'r') as f:
        prefixes = json.load(f)

    return prefixes[str(message.guild.id)]

client = commands.Bot(command_prefix = get_prefix)
client.remove_command('help')

game = cycle(["Watching over... 1 server, lol", "Created by Rob0tron, yeah"])
random_colors = ['red', 'blue', 'green', 'purple', 'pink', 'yellow']
random_color = random.choice(random_colors)
banned_words = ["lol"]
spamperms = False

@client.event
async def on_ready():
    print("I am ready")
    change_status.start()

@client.event
async def on_member_join(member):
    channel = client.get_channel(796673168202006548)
    embed = discord.Embed(title = f"Sup, {user.name}, welcome to {ctx.guild.name}" , description = f"Yo, I'm Broke Bot created by Rob0tron. Welcome to {ctx.guild.name}. I am the mod bot of this server. To have a LOT of fun here, pls check out the rules of this server. If you need some help with this server, contact the admin of this server Type -help for help with my commands. I hope you have gr8 time here. :ok_hand: .", color = discord.Color.purple())
    embed.set_thumbnail(url=ctx.guild.icon_url)
    embed.set_footer("Thank you soooo much for joining this server")
    await member.send(embed=embed)
    embed1 = discord.Embed(title = f"Arrival at {ctx.guild.name}", description = f"{member.mention} has joint {ctx.guild.name}. Hope he has a great time here.")
    await channel.send()

@client.event
async def on_member_remove(member):
    embed = discord.Embed(title = "A Departure :sob: }" , description = f"{member.mention} has left {ctx.guild.name}. Let's hope we'll get a replacement", color = discord.Color.blue())
    embed.set_thumbnail(url=ctx.guild.icon_url)
    embed.set_footer("#We will not give up")

@client.event
async def on_guild_join(guild):
    with open("prefixes.json", 'r') as f:
        prefixes = json.load(f)

    prefixes[str(guild.id)] =  '-'

    with open("prefixes.json", 'w') as f:
        json.dump(prefixes,f, indent=4)

@client.event
async def on_guild_remove(guild):
    with open("prefixes.json", 'r') as f:
        prefixes = json.load(f)

    prefixes.pop[str(guild.id)]

    with open("prefixes.json", 'w') as f:
        json.dump(prefixes,f, indent=4)

# @client.event
# async def on_command_error(ctx,error):
#     if isinstance(error, commands.MissingPermissions):
#         await ctx.send("You DO NOT have the required perms to do that :sob: ")
#         await ctx.message.delete()
#
#     elif isinstance(error, commands.MissingRequiredArgument):
#         await ctx.send("Pls enter all the required arguments for that command :computer: ")
#         await ctx.message.delete()
#
#     else:
#         raise

@client.event
async def on_message(message):
    messageAuthor = message.author

    if banned_words != None and (isinstance(message.channel, discord.channel.DMChannel) == False):
        for banned_word in banned_words:
            if banned_word.lower() in message.content.lower():
                await message.delete()
                await message.channel.send(f"{messageAuthor.mention} your message was removed since it contained a banned word :triumph: " )
                # await messageAuthor.send(f"{messageAuthor.mention} ARE YOU KIDDING MAN !!! Stop using such words :rage:")
                # messageAuthor.warn+

    await client.process_commands(message)

# #############################################################################################
#
#
#
# Commands from here
#
#
# #############################################################################################

@client.command(aliases=["prefix", "cp"])
@commands.has_permissions(administrator=True)
async def changeprefix(ctx, prefix):

    with open("prefixes.json", 'r') as f:
        prefixes = json.load(f)

    prefixes[str(ctx.guild.id)] =  prefix

    with open("prefixes.json", 'w') as f:
        json.dump(prefixes,f, indent=4)

    await ctx.send(f"The prefix for {ctx.guild.name} was changed to {prefix}")

@client.command()
async def ping(ctx):
    await ctx.send(f"Pong! I answered in like {round(client.latency * 1000 )} ms !!!")#

@client.command(aliases=["8ball"])#
async def _8ball(ctx, *, question): # asterix b'coz of spaces in question
    responses = ["It is decidedly so", "Without a doubt" ,"Yes – definitely",  "You may rely on it",  "As I see it, yes",  "Most likely", "Outlook good",  "Yes, Signs point to yes," "Reply hazy, try again",  "Ask again later",  "Better not tell you now", "Cannot predict now",  "Concentrate and ask again", "Dont count on it", "My reply is no", "My sources say no", "Outlook not so good", "Very doubtful"]
    await ctx.send(f" :8ball: {random.choice(responses)}")

@client.command(aliases=['c', 'purge', 'delete', 'dlt'])#
@commands.has_permissions(manage_messages=True)
async def clear(ctx, amount:int):

    await ctx.channel.purge(limit=amount)
    await ctx.send(f":negative_squared_cross_mark: Cleared **{amount}** messages ...")
    time.sleep(2)
    await ctx.channel.purge(limit=1)

@client.command(aliases=['k', 'chuck', 'remove'])#
@commands.has_permissions(kick_members=True)
async def kick(ctx, user : discord.Member, * , reason=" no reason provided"):
    await member.send(f"You got kicked out from {ctx.guild.name} because of {reason}")
    await ctx.send(f"Kicked :leg: out {user}, reason is {reason}")
    await user.kick(reason=reason)

@client.command(aliases=['guildstats'])
@commands.has_permissions(send_messages=True)
async def serverstats(ctx):
    embed = discord.Embed(title = "Server Statistics", description = f"Name : {ctx.guild.name}", color = discord.Color.red())
    embed.add_field(name=f"No. of members", value=ctx.guild.members)

@client.command(aliases=['b'])
@commands.has_permissions(ban_members=True)#
async def ban(ctx, user : discord.Member, *, reason=" no reason provided"):
    await user.ban(reason=reason)
    await member.send(f"You got banned in {ctx.guild.name} because of {reason}")
    await ctx.send(f"Banned {user.mention}, reason is {reason}")

@client.command(aliases=['ub'])#
@commands.has_permissions(ban_members=True)
async def unban(ctx, *, member):
    banned_users = await ctx.guild.bans()
    member_name, member_discriminator = member.split('#')

    for ban_entry in banned_users:
        user = ban_entry.user

        if(user.name, user.discriminator) == (member_name, member_discriminator):
            await ctx.guild.unban(user)
            await ctx.send(f"Unbanned {user.mention}")
            return
        else:
            await ctx.send(f"{member} is not a previosly banned member")

@client.command(aliases=['p', 'info', 'whois'])#
async def profile(ctx, *, user : discord.Member):
    embed = discord.Embed(title = "User profile" , description = f"Name: {user.name}", color = discord.Color.red())
    embed.add_field(name = "ID", value = user.id, inline = True)
    embed.add_field(name = "Description", value = user.mention, inline = True)
    embed.add_field(name = f"Roles in {ctx.guild.name}: ", value = user.roles.name, inline = False)
    embed.set_thumbnail(url=user.avatar_url)
    embed.set_footer(icon_url=ctx.author.avatar_url, text = f"Profile of {user} requested by {ctx.author}")
    await ctx.send(embed=embed)

@client.command(aliases=["censored", "addcensored"])
@commands.has_permissions(manage_messages=True)#
async def addbanned(ctx, *, word):
    if word.lower() in banned_words:
        await ctx.message.delete()
        await ctx.send("This word is already banned")
    else:
        banned_words.append(word.lower())
        await ctx.message.delete()
        await ctx.send("Word added to banned words list")

@client.command(aliases=["rmbanned", "rmcensored"])#
@commands.has_permissions(administrator=True)
async def removebanned(ctx, *, word):
    if word.lower() in banned_words:
        await ctx.message.delete()
        banned_words.remove(word.lower())
        await ctx.send("Word removed from banned words list")
    else:
        await ctx.message.delete()
        await ctx.send("This word is not in the banned word list")

@client.command()
@commands.has_permissions(administrator=True)
async def showbanned(ctx):
    await ctx.send(f"Banned list: {banned_words}")
    time.sleep(5)
    await ctx.chanel.purge(limit=1)

@client.command(aliases=['m', 'shutup'])
@commands.has_permissions(manage_messages=True)#
async def mute(ctx, user : discord.Member, *, reason= "no reason provided"):
    guild = ctx.guild
    muted_role = discord.utils.get(guild.roles, name="MUTED")

    if  not muted_role:
        muted_role = await guild.create_role(name="MUTED")
        for channel in guild.channels:
            await channel.set_permissions(muted_role, speak=False, send_messages=False, add_reactions=False, attach_files=False, read_message_history=False)
    else:
        for channel in guild.channels:
            await channel.set_permissions(muted_role, speak=False, send_messages=False, add_reactions=False, attach_files=False, read_message_history=False)

    await user.add_roles(muted_role, reason=reason)
    await ctx.send(f"Muted {user} for {reason}")
    await user.send(f"You were muted in {ctx.guild.name} for {reason}")

@client.command(aliases=['um'])
@commands.has_permissions(manage_messages=True)#
async def unmute(ctx, user : discord.Member):
    guild = ctx.guild
    muted_role = discord.utils.get(guild.roles, name="MUTED")

    await user.remove_roles(muted_role)
    await ctx.send(f"{user} has been unmuted")
    await user.send(f"You have been unmuted in {ctx.guild.name}")

@client.command(aliases=['l', 'lockdown'])
@commands.has_permissions(manage_channels=True)
async def lock(ctx, channel:discord.TextChannel=None):
    channel = ctx.channel

    for channel in ctx.guild.channels:
        await channel.set_permissions(ctx.guild.edit_role(everyone), send_messages=False)
        await ctx.send(f"{channel} locked down ")

@client.command(aliases=['w', 'hi'])
async def welcome(ctx, *, user : discord.Member):
    embed = discord.Embed(title = f"Sup, {user.name}, welcome to {ctx.guild.name}" , description = f"Yo, I'm Broke Bot created by Rob0tron. Welcome to {ctx.guild.name}. I am the mod bot of this server. To have a LOT of fun here, pls check out the rules of this server. If you need some help with this server, contact the admin of this server Type -help for help with my commands. I hope you have gr8 time here. :ok_hand: .", color = discord.Color.purple())
    embed.set_thumbnail(url=ctx.guild.icon_url)
    await ctx.send(embed=embed)

@client.command(aliases=['cr', 'creater', 'whomadeyou'])
async def credits(ctx):
    await ctx.send("Me am created by Rob0tron. Who is this great Rob0tron, you may ask......")
    time.sleep(3)
    await ctx.send("PONDER UPON IT :thinking: ")

@client.command()
async def spam(ctx, user : discord.Member, number, *, message):
    counter = 0

    while counter != number:
        await user.send(message)
                # await channel.purge(limit=1)
        counter + 1
    if counter == number:
        counter = 0
                # return
    else:
        ctx.send("If you wanna spam sooooooo much, go do it on your own. Limit is 15")

@client.command()
async def spam_perms(ctx, val=False):
    if val == True:
        spamperms=True
    else:
        spamperms=False

@client.command(aliases=[])
async def help(ctx):
    author = ctx.message.message

@client.command()
async def youtube(ctx, *, search):

    query_string = urllib.parse.urlencode({
         'search_query' : search
    })
    htm_content = urllib.request.urlopen(
        'http://www.youtube.com/results?'+ query_string
    )
    search_results = re.findall('href=\"\\/watch\\?v=(.{11})', htm_content.read().decode())
    await ctx.send('http://www.youtube.com/watch?v=' + search_results[0])

# #############################################################################################
#
#
#
# Errors from here
#
#
# #############################################################################################

@_8ball.error
async def _8ball_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="8ball command", description="What you wanna ask man ??? eg: **-8ball Will it rain today ?**", color = discord.Color.red())
    await ctx.send(embed=embed)

@clear.error
async def clear_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Clear command", description="Enter how many messages you wanna delete. eg: **-clear 10**", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Sorry you do not the perms required to clear messages :sob: ")
    elif isinstance(error, commands.BadArgument):
        await ctx.send("Man can you not enter a number instead of words :rage: !!!")
        embed = discord.Embed(title="Clear command", description="Enter how many messages you wanna delete. eg: **-clear 10**", color = discord.Color.red())
    else:
        raise
    await ctx.send(embed=embed)

@kick.error
async def kick_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Kick command", description="Who do you want to kick ? eg: **-kick [@username] ((optional) reason) **", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Sorry you do not the perms required to kick members :sob: ")
    elif isinstance(error, commands.CommandInvokeError):
        await ctx.send("You cannot kick moderators :lock:")
    elif isinstance(error, commands.MemberNotFound):
        await ctx.send("Don't try to fool me :laughing:, there is no such member in the server")
        embed = discord.Embed(title="Kick command", description="Who do you want to kick ? eg: **-kick [@username] (optional reason) **", color = discord.Color.red())
    else:
        raise
    await ctx.send(embed=embed)

@ban.error
async def ban_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Ban command", description="Who do you want to ban ? eg: **-ban [@username] (optional reason) **", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Sorry you do not the perms required to ban members :sob: ")
    elif isinstance(error, commands.CommandInvokeError):
        await ctx.send("You cannot ban moderators :lock:")
    elif isinstance(error, commands.MemberNotFound):
        await ctx.send("Banning unexistant members :rolling_eyes: ...")
        embed = discord.Embed(title="Ban command", description="This is how you ban those who :beetle: you:  **-ban [@username] (optional reason) **", color = discord.Color.green())
    else:
        raise
    await ctx.send(embed=embed)

@unban.error
async def unban_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Unban command", description="Who do you want to unban ? eg: **-unban [@username] **", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Wanna unban your friend heh :unamused:. Sorry you do not the perms required to unban members")
    elif isinstance(error, commands.CommandInvokeError):
        await ctx.send("You cannot unban moderators :lock:")
    elif isinstance(error, commands.MemberNotFound):
        await ctx.send("This member has not been banned previosly :negative_squared_cross_mark:")
        embed = discord.Embed(title="Unban command", description="Who do you want to unban ? Here's how you use this command **-unban [@username]**", color = discord.Color.red())

@profile.error
async def profile_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Profile command", description="Who's profile you wanna view :smirk: ??? This is how you use this command: **-profile [@username] **", color = discord.Color.red())
    elif isinstance(error, commands.MemberNotFound):
        await ctx.send("No such member exists in this server :negative_squared_cross_mark:")
        embed = discord.Embed(title="Unban command", description="Here's how you use the profile command **-profile [@username]**", color = discord.Color.red())
    await ctx.send(embed=embed)

@addbanned.error
async def addbanned(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Add banned words command", description="Add a banned word that cannot be used in this server :zipper_mouth:  eg: **-addbanned [banned word] **", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Sorry you do not the perms required to add banned words :cry:")
    ctx.send(embed=embed)

@removebanned.error
async def removebanned(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Remove banned words command", description="Remove a banned word from this server. Now it can be used.  eg: **-removebanned [banned word] **", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Sorry you do not the perms required to remove banned words :smirk:")
    ctx.send(embed=embed)

@mute.error
async def mute_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Mute command", description="Who do you want to mute ? eg: **-mute [@username] ((optional) reason) **", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Sorry you do not the perms required to kick members :sob: Contact the mod or admin and ask them to mute the guy who is spamming you... ")
    elif isinstance(error, commands.CommandInvokeError):
        await ctx.send("You cannot mute moderators :lock:")
    elif isinstance(error, commands.MemberNotFound):
        await ctx.send("Don't try to fool me :laughing:, there is no such member in the server")
        embed = discord.Embed(title="Mute command", description="Who do you want to mute ? eg: **-mute [@username] (optional reason) **", color = discord.Color.red())
    else:
        raise
    await ctx.send(embed=embed)

@unmute.error
async def unmute_error(ctx, error):
    if isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Unmute command", description="Who do you want to unmute ? eg: **-unmute [@username] ((optional) reason) **", color = discord.Color.red())
    elif isinstance(error, commands.MissingPermissions):
        ctx.send("Sorry you do not the perms required to unmute members :sob:")
    elif isinstance(error, commands.CommandInvokeError):
        await ctx.send("FOOLED YOU !!! If mods can't be muted, how will you unmute em' :rofl:")
    elif isinstance(error, commands.MemberNotFound):
        await ctx.send("No such member in this server")
        embed = discord.Embed(title="Unmute command", description="Who do you want to unmute ? eg: **-unmute [@username] (optional reason) **", color = discord.Color.red())
    else:
        raise
    await ctx.send(embed=embed)

@showbanned.error
async def showbanned_error(ctx, error):

    if isinstance(error, commands.MissingPermissions):
        ctx.send("Nope :lock:, you can't see that")
    else:
        raise
    await ctx.send(embed=embed)
    if isinstance(error, commands.MemberNotFound):
        await ctx.send("No such member in this server")
        embed = discord.Embed(title="Unmute command", description="Who do you want to unmute ? eg: **-unmute [@username] (optional reason) **", color = discord.Color.red())
    else:
        raise
    await ctx.send(embed=embed)

@welcome.error
async def welcome_error(ctx, error):
    if isinstance(error, commands.MemberNotFound):
        await ctx.send("How can you welcome an unexistant member :rolling_eyes:")
        embed = discord.Embed(title="Welcome command", description="Wanna welcome a newbie ??? Here's how you use this command. eg: **-welcome [@username]**", color = discord.Color.red())
    elif isinstance(error, commands.MissingRequiredArgument):
        embed = discord.Embed(title="Welcome command", description="Enter a user who you wanna welcome man... Here's how you use this command. eg: **-welcome [@username]**", color = discord.Color.red())
    else:
        raise
    await ctx.send(embed=embed)

@changeprefix.error
async def changeprefix_error(ctx, error):
    if isinstance(error, commands.MissingPermissions):
        await ctx.send("Sorry you need to be an admin to change my prefix")

    elif isinstance(error, commands.MissingRequiredArgument):
         embed = discord.Embed(title="Changeprefix command", description="This is how you can change prefix eg: **-prefix [new_prefix]**", color = discord.Color.red())
    else:
         raise
    await ctx.send(embed=embed)


# #############################################################################################
#
#
#
# Loops from here
#
#
# #############################################################################################

@tasks.loop(seconds=10000)
async def change_status():
    await client.change_presence(status = discord.Status.idle, activity=discord.Game(next(game)))

# @client.command()
# async def load(ctx, extension):
#     client.load_extension(f"cogs.{extension}")
#
# @client.command()
# async def unload(ctx, extension):
#     client.unload_extension(f"cogs.{extension}")
#
# for file_name in os.listdir('./cogs'):
#     if file_name.endswith(.py):
#         client.load_extension(f"cogs.{filename[:-3]}")
#
client.run("ODEzNjcxMTczMDY1NTM5NTk0.YDSsVA.A0e_3mNdHuT6krLH2eTTNqSX9xk")
