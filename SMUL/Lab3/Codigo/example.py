import music21
import os

def main():
    
    score = music21.converter.parse('./bach/bwv_A_Major.midi')
    key = score.analyze('Krumhansl')
    print('Best Prediction = ', key.tonic.name, key.mode, key.correlationCoefficient)
    print('Second best Prediction = ', key.alternateInterpretations[0].tonic.name, key.alternateInterpretations[0].mode, key.alternateInterpretations[0].correlationCoefficient)
    print('Third best Prediction = ', key.alternateInterpretations[1].tonic.name, key.alternateInterpretations[1].mode, key.alternateInterpretations[1].correlationCoefficient)
    print('Worst Prediction = ', key.alternateInterpretations[22].tonic.name, key.alternateInterpretations[22].mode, key.alternateInterpretations[22].correlationCoefficient)

    #krumhansl
    """ print('Krumhansl')
    key = score.analyze('Krumhansl')
    print('Best Prediction = ', key.tonic.name, key.mode, key.correlationCoefficient)
    print('Second best Prediction = ', key.alternateInterpretations[0].tonic.name, key.alternateInterpretations[0].mode, key.alternateInterpretations[0].correlationCoefficient)
    print('Third best Prediction = ', key.alternateInterpretations[1].tonic.name, key.alternateInterpretations[1].mode, key.alternateInterpretations[1].correlationCoefficient)
    print('Worst Prediction = ', key.alternateInterpretations[22].tonic.name, key.alternateInterpretations[22].mode, key.alternateInterpretations[22].correlationCoefficient)
    print('Scale', key.getScale(key.mode).chord)
    key2 = music21.analysis.discrete.KrumhanslSchmuckler(score)
    print(key2.getSolution(score))

    #temperley
    print('Temperley')
    key = score.analyze('temperley')
    print('Best Prediction = ', key.tonic.name, key.mode, key.correlationCoefficient)
    print('Second best Prediction = ', key.alternateInterpretations[0].tonic.name, key.alternateInterpretations[0].mode, key.alternateInterpretations[0].correlationCoefficient)
    print('Third best Prediction = ', key.alternateInterpretations[1].tonic.name, key.alternateInterpretations[1].mode, key.alternateInterpretations[1].correlationCoefficient)
    print('Worst Prediction = ', key.alternateInterpretations[22].tonic.name, key.alternateInterpretations[22].mode, key.alternateInterpretations[22].correlationCoefficient)
    key2 = music21.analysis.discrete.TemperleyKostkaPayne(score)
    print(key2.getSolution(score))

    #bellman
    print('Bellman')
    key = score.analyze('bellman')
    print('Best Prediction = ', key.tonic.name, key.mode, key.correlationCoefficient)
    print('Second best Prediction = ', key.alternateInterpretations[0].tonic.name, key.alternateInterpretations[0].mode, key.alternateInterpretations[0].correlationCoefficient)
    print('Third best Prediction = ', key.alternateInterpretations[1].tonic.name, key.alternateInterpretations[1].mode, key.alternateInterpretations[1].correlationCoefficient)
    print('Worst Prediction = ', key.alternateInterpretations[22].tonic.name, key.alternateInterpretations[22].mode, key.alternateInterpretations[22].correlationCoefficient)

    key2 = music21.analysis.discrete.TemperleyKostkaPayne(score)
    print(key2.getSolution(score)) """




if __name__ == "__main__":
    main()