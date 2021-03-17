
import discord
from discord.ext import commands, tasks

client = commands.Bot(command_prefix = "_")

@client.event
async def on_ready():
    print("I am ready")
    await channel.send("hmmmm")

client.run("Nzc1NzU2MzE2MDIyOTMxNDc2.X6q9Xg.k0mIhzsSHfiC1xGq4_ZTTYXr6j4")
