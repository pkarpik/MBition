import sys
import openai

def gpt3(stext):

    openai.api_key = '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'
    response = openai.Completion.create(
        engine = "text-davinci-002",
        prompt = """Q: what is the weather like today?\nA: Get Weather.
        \nQ: i heard a gossip.\nA: -.
        \nQ: what is the weather like in paris today?\nA: Get Weather.
        \nQ: tell me an interesting fact.\nA: Get Fact.
        \nQ: want to listen to a story.\nA: Get Story.
        \nQ: get a phone.\nA: Get Phone.
        \nQ: i would like to know this information.\nA: Get Information.
        \nQ: tell me about the weather.\nA: Get Weather.
        \nQ: the weather is bad.\nA: -.
        \nQ: what is the weather like in paris?\nA: Get Weather.
        \nQ: the fact was interesting.\nA: -.
        \nQ: get address.\nA: Get Address.""" + "\n\nQ:" + stext + "\nA: ",
                temperature = 0,
                max_tokens = 6,
                top_p = 1,
                frequency_penalty = 0,
                presence_penalty = 0,
                stop=["."]
    )

    content = response.choices[0].text.split( '.' )

    file = open( "GPT3Response.txt", "w" )
    print( "Inquiry: " + stext )
    content[0] = content[0].replace('\n', '')
    content[0] = content[0].strip(' ')
    file.write( content[0] )
    file.close()


gpt3( sys.argv[1] )
