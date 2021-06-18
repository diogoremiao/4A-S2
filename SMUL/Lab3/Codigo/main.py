import music21
import os

class result:
  key = music21.key.Key() # A class variable counts its instantiations 
  def __init__(self, answer, prediction):
    self.key = prediction
    self.answer = answer
    

##################################################
#get array with all files in a directory
def get_file_names(directory):

    samples = []

    for file in os.listdir(directory):
        filename = os.fsdecode(file)
        if filename.endswith(".midi") or filename.endswith(".mid"): 
            #print(filename)
            samples.append(os.path.join(directory, filename))
        else:
            continue
    
    return sorted(samples)

##################################################
#create a prediction based on krumhansl key profile
def profile_prediction(samples, profile):

    results = [] 
    for sample in samples:
        #print('\n'+sample)
        #parse to Stream class
        score = music21.converter.parse(sample)
        #print('parsed')
        #create key class for krumhansl profiles using krumhansl algorithm
        key = score.analyze(profile)
        results.append(result(sample,key))

    return results


##################################################
#create a prediction based on krumhansl key profile
def compare_result_prediction(predictions):

    results=[0, 0, 0, 0]
    for obj in predictions:
        #print(obj.answer)
        #C_Major##################
        if 'C_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'C' and obj.key.mode == 'major':
                results[0]+=1                
            elif music21.key.Key('C').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('C').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #C_Minor##################
        elif 'C_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'C' and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('c').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('C').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1    
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #C#_Major##################
        elif 'C#_Major' in obj.answer or 'Db_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'C#' or obj.key.tonic.name == 'D-') and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('C#').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('C#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #C#_Minor##################
        elif 'C#_Minor' in obj.answer or 'Db_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'C#' or obj.key.tonic.name == 'D-') and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('c#').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('C#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #D_Major##################
        elif 'D_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'D' and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('D').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('D').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #D_Minor##################
        elif 'D_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'D' and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('d').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('D').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #D#_Major##################
        elif 'D#_Major' in obj.answer or 'Eb_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'D#' or obj.key.tonic.name == 'E-') and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('D#').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('D#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #D#_Minor##################
        elif 'D#_Minor' in obj.answer or 'Eb_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'D#' or obj.key.tonic.name == 'E-') and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('d#').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('D#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #E_Major##################
        elif 'E_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'E' and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('E').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('E').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)
                
        #E_Minor##################
        elif 'E_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'E' and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('e').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('E').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #F_Major##################
        elif 'F_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'F' and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('F').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('F').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #F_Minor##################
        elif 'F_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'F' and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('f').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('F').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #F#_Major##################
        elif 'F#_Major' in obj.answer or 'Gb_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'F#' or obj.key.tonic.name == 'G-') and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('F#').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('F#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #F#_Minor##################
        elif 'F#_Minor' in obj.answer or 'Gb_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'F#' or obj.key.tonic.name == 'G-') and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('f#').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('F#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #G_Major##################
        elif 'G_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'G' and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('G').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('G').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #G_Minor##################
        elif 'G_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'G' and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('g').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('G').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #G#_Major##################
        elif 'G#_Major' in obj.answer or 'Ab_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'G#' or obj.key.tonic.name == 'A-') and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('G#').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('G#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #G#_Minor##################
        elif 'G#_Minor' in obj.answer or 'Ab_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'G#' or obj.key.tonic.name == 'A-') and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('g#').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1
            elif music21.key.Key('G#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #A_Major##################
        elif 'A_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'A' and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('A').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('A').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #A_Minor##################
        elif 'A_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'A' and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('a').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('A').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #A#_Major##################
        elif 'A#_Major' in obj.answer or 'Bb_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'A#' or obj.key.tonic.name == 'B-') and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('A#').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('A#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #A#_Minor##################
        elif 'A#_Minor' in obj.answer or 'Bb_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if (obj.key.tonic.name == 'A#' or obj.key.tonic.name == 'B-') and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('a#').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('A#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #B_Major##################
        elif 'B_Major' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'B' and obj.key.mode == 'major':
                results[0]+=1 
            elif music21.key.Key('B').relative.tonic.name == obj.key.tonic.name and 'minor' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('A#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        #B_Minor##################
        elif 'B_Minor' in obj.answer:
            #print(obj.key.tonic.name, obj.key.mode)
            if obj.key.tonic.name == 'B' and obj.key.mode == 'minor':
                results[0]+=1 
            elif music21.key.Key('b').relative.tonic.name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[1]+=1 
            elif music21.key.Key('A#').getDominant().name == obj.key.tonic.name and 'major' == obj.key.mode:
                results[2]+=1
            elif obj.key.parallel.tonic.name in obj.answer:
                results[3]+=1
            else:
                print(obj.answer)
                print(obj.key.tonic.name, obj.key.mode)

        
    return results
##################################################

def get_prediction(directory, profile):

    samples = get_file_names(directory)
    results = profile_prediction(samples, profile)
    precision = compare_result_prediction(results)

    return samples, results, precision

def print_results(precision, results):

    print('Tonic = ', round(precision[0] / len(results) * 100, 2), '%')
    print('Relative = ', round(precision[1] / len(results) * 100, 2), '%')
    print('Dominant = ', round(precision[2] / len(results) * 100, 2), '%')
    print('Parallel = ', round(precision[3] / len(results) * 100, 2), '%')

    return 0

def main():
    
    #Bach
    print('Chopin Etudes')
    directory = './chopin'
    
    print('\nKrumhansl')
    profile = 'krumhansl'
    samples_bach, results_bach, precision_bach = get_prediction(directory,profile)
    print_results(precision_bach, results_bach)

    print('\nAarden')
    profile = 'arden'
    samples_bach, results_bach, precision_bach = get_prediction(directory,profile)
    print_results(precision_bach, results_bach)

    print('\nCraig')
    profile = 'simple'
    samples_bach, results_bach, precision_bach = get_prediction(directory,profile)
    print_results(precision_bach, results_bach)

    print('\nTemperley')
    profile = 'temperley'
    samples_bach, results_bach, precision_bach = get_prediction(directory,profile)
    print_results(precision_bach, results_bach)

    print('\nBellman')
    profile = 'bellman'
    samples_bach, results_bach, precision_bach = get_prediction(directory,profile)
    print_results(precision_bach, results_bach)


    
if __name__ == "__main__":
    main()