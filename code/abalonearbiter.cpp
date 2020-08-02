#include "abalonearbiter.h"

//#define qDebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug //for debugging

AbaloneArbiter::AbaloneArbiter(AbaloneBoard* board) : Arbiter(board)
{

    ///Build the direction map
    directionMap[dNone] = None;
    directionMap[dHorizontalRight] = HorizontalRight;
    directionMap[dHorizontalLeft] = HorizontalLeft;
    directionMap[dSlantedRightUp] = SlantedRightUp;
    directionMap[dSlantedRightDown] = SlantedRightDown;
    directionMap[dSlantedLeftUp] = SlantedLeftUp;
    directionMap[dSlantedLeftDown] = SlantedLeftDown;

    ///Build te direction array
    directionArray.push_back(HorizontalRight);
    directionArray.push_back(HorizontalLeft);
    directionArray.push_back(SlantedRightUp);
    directionArray.push_back(SlantedRightDown);
    directionArray.push_back(SlantedLeftUp);
    directionArray.push_back(SlantedLeftDown);

    ///Start with player 0
    setCurrentPlayer(0);

}

AbaloneArbiter::~AbaloneArbiter()
{
}

bool AbaloneArbiter::isValidPos(QPoint position_to_check) const
{
    if(position_to_check.x() + position_to_check.y() < 4 ||
       position_to_check.x() + position_to_check.y() > 12 ||
       position_to_check.x() < 0 || position_to_check.x() > 8 ||
       position_to_check.y() < 0 || position_to_check.y() > 8)
    {
       return false;
    }
    else
    {
       return true;
    }
}

bool AbaloneArbiter::canMove(QPoint from, QPoint to) const //Main move check logic in canMoveTriad
{
    //if from is not empty and to is empty
    if (determineTypeOfPiece(from) != pEmpty && determineTypeOfPiece(to) == pEmpty)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AbaloneArbiter::setCurrentPlayer(int owner)
{
    currentPlayer = owner;
}

int AbaloneArbiter::getCurrentPlayer()
{
    return currentPlayer;
}

bool AbaloneArbiter::canMoveTriad(QPoint to)
{
    bool result = true;
    QPoint movementDirection = directionMap[pairDirection(currentTriad.back(),to)];
    strongMovement = (triadDirection() == pairDirection(currentTriad.back(),to));
    if(!strongMovement)
    {
      //bool weakMovementPossible = true;
      for (auto it = currentTriad.begin() ; it != currentTriad.end() && result == true ; it++) //check each "to" place in the triad
      {
          QPoint space_to_move_to = *it + movementDirection;
          type_of_piece type = determineTypeOfPiece(space_to_move_to);
          if(type != pEmpty)
          {
              //if one of the places is not empty then we cant move there with a weak movement
              result = false;
              //qDebug() << "In weak movement, can't move from " << *it << " to " << space_to_move_to;
          }
      }
      //return weakMovementPossible;
    }
    else //strongMovement
    {
        formOppositeTriad(to);
        type_of_piece type_of_edge = determineTypeOfPiece(oppositeTriad.back());
        if(! //Negative so we can set result to false, since the default is true
          ((type_of_edge == pInvalid //the edge must be either invalid, meaning we are pushing the piece outside the board.
          || type_of_edge == pEmpty) //or empty, meaning we are moving the enemy triad.
          && (currentTriad.size() > (oppositeTriad.size() - 1)))) //Additionally, our triad must be strictly bigger.
        {
           result = false;
        }
    }
    return result;
}

AbaloneArbiter::type_of_piece AbaloneArbiter::determineTypeOfPiece(QPoint coordinates_to_check) const
{
    if(!isValidPos(coordinates_to_check))
    {
        return pInvalid;
    }
    else
    {
        Piece* current_piece = dynamic_cast<AbaloneBoard*>(board)->getPiece(coordinates_to_check);

        if(current_piece == nullptr)
        {
            return pEmpty;
        }
        if(current_piece->getOwner() == currentPlayer)
        {
            return pOwn;
        }
        else
        {
            return pEnemy;
        }
    }
}

void AbaloneArbiter::formOppositeTriad(QPoint beginning_of_opposite_triad)
{
    oppositeTriad.clear(); //reset it before we start filling it
    QPoint movement_direction = directionMap[pairDirection(currentTriad.back(),beginning_of_opposite_triad)];
    int i = 0;
    bool edge_reached = false;
    QPoint current_position;
    while(i < 4 && !edge_reached)
    {
        current_position = beginning_of_opposite_triad + (movement_direction * i);
        oppositeTriad.push_back(current_position);
        i++;
        if(determineTypeOfPiece(current_position) != pEnemy)
        {
            edge_reached = true;
        }
    }
}

void AbaloneArbiter::moveTriad(QPoint to) //Doesnt test, the validity of the movement must be tested with canMoveTriad first
{
    QPoint movementDirection = directionMap[pairDirection(currentTriad.back(),to)];
    strongMovement = (triadDirection() == pairDirection(currentTriad.back(),to));
    if(!strongMovement)
    {
        qDebug() << "moveTriad: starting a weak movement to " << to << endl;
        for (auto it = currentTriad.begin(); it != currentTriad.end();it++)
             {
                 board->movePiece(*it, *it + movementDirection);
             }
    }
    else
    {
         qDebug() << "moveTriad: starting a STRONG movement to " << to << endl;
        QPoint space_to_move_to = (currentTriad.back() + movementDirection);
        if(dynamic_cast<AbaloneBoard*>(board)->getPiece(space_to_move_to) != nullptr)
        {
             qDebug() << "moveTriad: CONFLICT detected in strong movement. " << endl;
            formOppositeTriad(to); //We don't know if the last canMoveTriad was for this "to" or another one, just reform it and be safe
            if(determineTypeOfPiece(oppositeTriad.back()) == pInvalid) //Means we are pushing a piece out of the board and is ok to overwrite it in the methods below.
            {                             
                oppositeTriad.pop_back(); //remove the invalid edge
                dynamic_cast<AbaloneBoard*>(board)->addLostPiece(dynamic_cast<AbaloneBoard*>(board)->getPiece(oppositeTriad.back())); //save the piece we are going to overwrite (destroy) in the lostPieces vector
                currentTriad.insert(currentTriad.end(),oppositeTriad.begin(),oppositeTriad.end());
                /*
                for (auto rit = oppositeTriad.rbegin(); rit != oppositeTriad.rend() - 1; rit++)
                {                   
                   board->movePiece(*(rit+1),*rit);
                }
                */
                for (auto rit = currentTriad.rbegin(); rit != currentTriad.rend() - 1; rit++)
                {
                   board->movePiece(*(rit+1),*rit);
                }
            }
            else //not killing an enemy piece, just bullying it, ALSO we assume it is a valid move (use canMoveTriad first, as usual)
            {
                currentTriad.insert(currentTriad.end(),oppositeTriad.begin(),oppositeTriad.end());
                /* //Instead of moving the oppositeTriad by itself just concatenate it to the main and do the usual move.
                for (auto rit = oppositeTriad.rbegin(); rit != oppositeTriad.rend() -1; rit++)
                {
                   board->movePiece(*(rit+1),*rit);
                }
                */
                for (auto rit = currentTriad.rbegin(); rit != currentTriad.rend() - 1; rit++)
                {
                   board->movePiece(*(rit+1),*rit);
                }
            }
        }
        else //NO conflict
        {
            qDebug() << "moveTriad: NO conflict detected in strong movement. " << endl;
            currentTriad.push_back(to);
             for (auto rit = currentTriad.rbegin(); rit != currentTriad.rend() - 1; rit++)
             {
                board->movePiece(*(rit+1),*rit);
             }
        }
    }
    setCurrentPlayer((currentPlayer+1) % 2); //Change players since a move has been commited
    currentTriad.clear(); //clear the triad
    oppositeTriad.clear(); //and the enemies
    qDebug() << "moveTriad: moving done, changing player to: " << currentPlayer;
}

AbaloneArbiter::direction AbaloneArbiter::pairDirection(QPoint from, QPoint to) //NEEDS TO CHECK CONTIGUITY FIRST
{
   direction result_direction = dNone;
   //qDebug() << "pairDirection: For directions from" << from << " and to " << to;
   if (from.x() != to.x() && from.y() == to.y()) //only x changes
   {
       if(from.x() < to.x())
       {
           result_direction = dHorizontalRight;
       }
       else
       {
           result_direction =  dHorizontalLeft;
       }
   }
   else if (from.x() == to.x() && from.y() != to.y())
   {
       if(from.y() < to.y())
       {
           result_direction = dSlantedRightDown;

       }
       else
       {
           result_direction = dSlantedLeftUp;
       }
   }
   else //both different
   {
       if(from.y() < to.y())
       {
           result_direction = dSlantedLeftDown;
       }
       else
       {
           result_direction = dSlantedRightUp;
       }
   }
   //qDebug() << " calculated direction to be " << result_direction << endl;
   return result_direction;
}

AbaloneArbiter::direction AbaloneArbiter::triadDirection()
{
    if(currentTriad.size() <= 1)
    {
        return dNone;
    }
    else //2 or more pieces in triad
    {
        std::vector<QPoint>::reverse_iterator rit = currentTriad.rbegin();
        return pairDirection(*(rit+1),*rit); //RIT+1 NEEDS TESTING TO SEE IF IT WORKS
    }
}


void AbaloneArbiter::tryToAddPieceToTriad(QPoint piece_to_add)
{
    if(pieceBelongsToCurrentPlayer(piece_to_add))
    {
        if(currentTriad.size() >= 3)
        {
            currentTriad.clear(); //resets the triad since it is trying to go above 3
            qDebug() << "tryToAddPieceToTriad: triad reset triggeered by going above 3";
        }
        else if(currentTriad.size() >= 1 && !contiguous(piece_to_add,currentTriad.back()))
        {
           currentTriad.clear(); //resets the triad since it is an noncontiguous piece
           qDebug() << "tryToAddPieceToTriad: triad reset triggeered by selecting noncontiguous piece";
        }
        else if(currentTriad.size() == 2) //needs to check that there are 2 in the triad before running currentTriad[1] or it will cause an error to run both conditionals in the same
        {
            if(pairDirection(currentTriad[0],currentTriad[1]) != pairDirection(currentTriad[1],piece_to_add))
            {
                currentTriad.clear(); //the last piece wasnt in the same direction (didnt form a straight line) thus reset the triad.
                qDebug() << "tryToAddPieceToTriad: triad reset triggeered by selecting a third piece that doesn't form a line";
            }
        }
        currentTriad.push_back(piece_to_add); //adds whatever was selected since it belongs to the current player
    }
}

bool AbaloneArbiter::contiguous(QPoint one, QPoint two)
{
    bool result = false;
    for(auto it = directionArray.begin() ; it != directionArray.end() && !result ; it++)
    {
        if(one == two + *it)
        {
            result = true;
        }
    }
    return result;
}


bool AbaloneArbiter::pieceBelongsToCurrentPlayer(QPoint selected_piece)
{
    return dynamic_cast<AbaloneBoard*>(board)->getPiece(selected_piece)->getOwner() == currentPlayer;
}

bool AbaloneArbiter::pieceBelongsToCurrentPlayer(Piece selected_piece)
{
    return selected_piece.getOwner() == currentPlayer;
}

void AbaloneArbiter::updateCanMoveList()
{
    canMoveList.clear(); //should always wipe it and create it anew.
    if(currentTriad.size() != 0)
    {
        QPoint currentCoordinatesToAdd;
        for(auto it = directionArray.begin(); it != directionArray.end();it++)
        {
            currentCoordinatesToAdd = currentTriad.back() + *it;
            //qDebug() << "updateCanMoveList: testing " << currentCoordinatesToAdd;
            if (canMoveTriad(currentCoordinatesToAdd))
            {
                canMoveList.push_back(currentCoordinatesToAdd);
                //qDebug() << "updateCanMoveList: commited " << currentCoordinatesToAdd;
            }
        }
    }
    printStructuresState();
}

bool AbaloneArbiter::checkCanMoveList(QPoint position_to_check)
{
    bool result = (find(canMoveList.begin(),canMoveList.end(),position_to_check) != canMoveList.end());
    //qDebug() << "checkCanMoveList returns: " << result << "for position: " << position_to_check << endl;
    return result;
}

int AbaloneArbiter::select(QPoint selected_coordinates)
{
    type_of_piece selected_piece_type = determineTypeOfPiece(selected_coordinates);

    switch (selected_piece_type) //In theory, pInvalid should be imposible to receive since this is limited by the buttons in the UI.
    {
        case pEmpty:
            qDebug() << "Empty space selected with a triad sized: " <<  currentTriad.size() << endl;
            if(currentTriad.size() != 0)
            {                
                if(checkCanMoveList(selected_coordinates))
                {
                    moveTriad(selected_coordinates);
                }
            }
        break;

        case pEnemy:
            qDebug() << "Enemy piece selected with a triad sized: " <<  currentTriad.size() << endl;
            if(currentTriad.size() > 1)//the piece is from the other player, the user is trying to push AND has pieces to do so
            {
                //check the "can move list"
                //if true, then commit a push
                if(checkCanMoveList(selected_coordinates))
                {
                    moveTriad(selected_coordinates);
                }
            }
        break;

        case pOwn:
            qDebug() << "Own piece selected with a triad sized: " <<  currentTriad.size() << endl;
            tryToAddPieceToTriad(selected_coordinates);
        break;

        default:
        assert(false); //unexpected type of piece

    }
    updateCanMoveList();

    return isGameOver();
}

int AbaloneArbiter::isGameOver() const
{
    size_t lostPiecesPlayer1 = 0;
    size_t lostPiecesPlayer2 = 0;
    for(auto lostPiece : dynamic_cast<AbaloneBoard*>(board)->getLostPieces())
        if (lostPiece->getOwner() == 0)
            ++lostPiecesPlayer1;
        else if(lostPiece->getOwner() == 1)
            ++lostPiecesPlayer2;
    if(lostPiecesPlayer1 == 6)
        return PLAYER_1_GAME_OVER;
    else if(lostPiecesPlayer2 == 6)
        return PLAYER_2_GAME_OVER;
    else
        return GAME_NOT_OVER;
}

void AbaloneArbiter::printStructuresState()
{
    qDebug() << "Current Triad: ";
    for(auto it = currentTriad.begin(); it != currentTriad.end(); it++)
    {
        qDebug() << *it;
    }
    qDebug() << endl;

    qDebug() << "canMoveList Sized: " << canMoveList.size() << " Contains: ";
    for(auto it = canMoveList.begin(); it != canMoveList.end(); it++)
    {
        qDebug() << *it;
    }
    qDebug() << endl;

    qDebug() << "Lost Pieces: " << dynamic_cast<AbaloneBoard*>(board)->getLostPieces().size() << endl;
}

